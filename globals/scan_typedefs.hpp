#pragma once
#ifndef SCAN_TYPEDEFS_HPP
#define SCAN_TYPEDEFS_HPP

#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Sparse>
#include <eigen3/Eigen/StdVector>
#include <fstream>
#include <iostream>
#include <memory>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <unordered_map>

#include "scan_gflags.h"
#include <omp.h>

#define NUM_ROTS 4

constexpr double PI = 3.14159265358979323846;
constexpr double maxPhi = 2.61946;

class BuildingScale {
private:
  double scale = -1;

public:
  double getScale();
  void update(double scale);
};

extern BuildingScale buildingScale;

namespace std {
template <> struct hash<std::vector<int>> {
  static constexpr double A = 1.6180339887498948482 * 1e5;
  hash<double> h;
  size_t operator()(const std::vector<int> &k) const;
};
} // std

namespace place {
class edge {
public:
  double pA, feA, feB, fx;
  double w, wSignificance;
  double panoW, panoSignificance;
  double distance;
  int numSim = 0, numDiff = 0;
  edge()
      : pA{0}, feA{0}, feB{0}, fx{0}, w{0}, wSignificance{0}, panoW{0},
        panoSignificance{0}, distance{0} {};
  edge(double pA, double feA, double feB, double fx, double w,
       double wSignificance)
      : pA{pA}, feA{feA}, feB{feB}, w{w}, wSignificance{wSignificance},
        panoW{0}, panoSignificance{0}, distance{0} {};
  double getWeight() const;
  friend std::ostream &operator<<(std::ostream &os, const place::edge &print);
};

class Wall {
public:
  struct side {
    std::vector<int> incident, owners;
    double distance = 10000.0;
    double weight = 0.0;
    int count = 0;
  };
  Wall() : normal{nullptr}, s{nullptr} {};
  ~Wall();
  void init(const Eigen::Vector2d &n);
  side &getSide(const Eigen::Vector2d &ray);
  const Eigen::Vector2d &getNormal();
  void changeNormal(const Eigen::Vector2d &n);

private:
  Eigen::Vector2d *normal;
  side *s;
};
} // place

namespace Eigen {
typedef Array<Eigen::Vector3f, Dynamic, Dynamic, RowMajor> ArrayXV3f;
typedef Array<place::edge, Dynamic, Dynamic> MatrixXE;
typedef Array<place::Wall::side, Dynamic, Dynamic> ArrayXH;
typedef Matrix<char, Dynamic, Dynamic> MatrixXb;
typedef Matrix<int, Dynamic, Dynamic, RowMajor> RowMatrixXi;
typedef Matrix<char, Dynamic, Dynamic, RowMajor> RowMatrixXb;
typedef Matrix<double, Dynamic, Dynamic, RowMajor> RowMatrixXd;
typedef Matrix<float, Dynamic, Dynamic, RowMajor> RowMatrixXf;
} // Eigen

typedef struct SHOT1344WithXYZ {
  std::shared_ptr<Eigen::VectorXf> descriptor;
  Eigen::Vector3d position;

  SHOT1344WithXYZ() : descriptor{std::make_shared<Eigen::VectorXf>(1344)} {};

  void writeToFile(std::ofstream &out);
  void loadFromFile(std::ifstream &in);

} SHOT1344WithXYZ;

typedef struct SPARSE352WithXYZ {
  typedef Eigen::SparseVector<float> VecType;
  std::shared_ptr<VecType> descriptor;
  Eigen::Vector3d position;

  SPARSE352WithXYZ() : descriptor{std::make_shared<VecType>(352)} {};
  void writeToFile(std::ofstream &out);
  void loadFromFile(std::ifstream &in);

} SPARSE352WithXYZ;

typedef struct SPARSE1344WithXYZ {
  typedef Eigen::SparseVector<float> VecType;
  std::shared_ptr<VecType> descriptor;
  Eigen::Vector3d position;

  SPARSE1344WithXYZ() : descriptor{std::make_shared<VecType>(1344)} {};

  void writeToFile(std::ofstream &out);
  void loadFromFile(std::ifstream &in);

} SPARSE1344WithXYZ;

namespace scan {
typedef struct PointXYZRGBA {
  Eigen::Vector3f point;
  float intensity;
  unsigned char rgb[3];

  void writeToFile(std::ofstream &out);
  void loadFromFile(std::ifstream &in);
} PointXYZRGBA;

typedef struct PointXYZRGB {
  Eigen::Vector3f point;
  unsigned char rgb[3];

  void writeToFile(std::ofstream &out);
  void loadFromFile(std::ifstream &in);
} PointXYZRGB;
} // scan

namespace place {
struct posInfo {
  double score = 0;
  double scanFP = 0;
  double fpScan = 0;
  int rotation = 0;
  int fpPixels = 0;
  int scanPixels = 0;
  int x = 0;
  int y = 0;

  friend std::ostream &operator<<(std::ostream &os,
                                  const place::posInfo *print);
  friend std::ostream &operator<<(std::ostream &os,
                                  const place::posInfo &print);

  bool operator==(const posInfo &o) const {
    return o.rotation == rotation && o.x == x && o.y == y;
  }
};

struct ExclusionMap {
  typedef Eigen::Array<const place::posInfo *, Eigen::Dynamic, Eigen::Dynamic,
                       Eigen::RowMajor>
      Map;
  Map *maps;
  double exclusionX, exclusionY;
  int rows, cols;

  ExclusionMap(double exclusionX, double exclusionY, int rows, int cols);
  ~ExclusionMap();

  Map &operator[](int r);
};

struct VoxelGrid {
  std::vector<Eigen::MatrixXb> v;
  Eigen::Vector3i zZ;
  size_t c;

  void writeToFile(std::ofstream &out);
  void loadFromFile(std::ifstream &in);
};

typedef struct {
  posInfo s;
  int scanNum;
} moreInfo;

struct node : public posInfo {
  double w;
  double nw;
  int color, id;
  node(const posInfo &s, double w, double nw, int color, int id)
      : posInfo{s}, w{w}, nw{nw}, color{color}, id{id} {};
  inline double getWeight() const { return nw; };
};

struct SelectedNode : public node {
  double agreement, norm;
  int label, numberOfCandidates;
  bool locked;
  SelectedNode(const node &o, double agreement, int label, bool locked,
               int numberOfCandidates)
      : node{o}, agreement{agreement}, norm{0}, label{label}, locked{locked},
        numberOfCandidates{numberOfCandidates} {};

  friend std::ostream &operator<<(std::ostream &os,
                                  const place::SelectedNode &p);
};

struct R2Node : public node {
  double agreement;
  bool locked;
  R2Node(const node &o, bool locked) : node{o}, agreement{0}, locked{locked} {};

  R2Node(const posInfo &s, double w, double nw, int color, int id, bool locked)
      : node{s, w, nw, color, id}, locked{locked} {};
  R2Node(const SelectedNode &s)
      : node{s}, agreement{s.agreement}, locked{s.locked} {};
};

typedef struct {
  int X1;
  int Y1;
  int X2;
  int Y2;
} rect;

struct MetaData {
  Eigen::Vector3i zZ;
  int x, y, z;
  double vox, s;
  void writeToFile(std::ofstream &out);
  void loadFromFile(std::ifstream &in);
};

class cube {
public:
  int X1, Y1, Z1;
  int X2, Y2, Z2;
  cube() : X1{0}, Y1{0}, Z1{0}, X2{0}, Y2{0}, Z2{0} {};
  int volume() {
    const int width = this->X2 - this->X1;
    const int length = this->Y2 - this->Y1;
    const int height = this->Z2 - this->Z1;
    return width * length * height;
  };

  friend std::ostream &operator<<(std::ostream &os, const place::cube &print);
};

struct Panorama {
  static constexpr double ScalingFactor = std::pow(2.0, 1.0 / 3.0);

  std::vector<cv::Mat> imgs;
  Eigen::RowMatrixXf rMap;
  std::vector<cv::Point2f> keypoints;
  Eigen::ArrayXV3f surfaceNormals;
  void writeToFile(const std::string &imgName, const std::string &dataName);
  void loadFromFile(const std::string &imgName, const std::string &dataName);

  const cv::Mat &operator[](int n);
};

template <class It, class UnaryFunc, class UnaryPredicate>
std::tuple<double, double> aveAndStdev(It first, It last, UnaryFunc selector,
                                       UnaryPredicate filter) {
  double average = 0;
  int count = 0;
  std::for_each(first, last, [&](auto &e) {
    if (filter(e)) {
      auto val = selector(e);
      if (Eigen::numext::isfinite(val)) {
        average += val;
        ++count;
      }
    }
  });
  average /= count;

  double sigma = 0;
  std::for_each(first, last, [&](auto &e) {
    if (filter(e)) {
      auto val = selector(e);
      if (Eigen::numext::isfinite(val))
        sigma += (val - average) * (val - average);
    }
  });
  sigma /= count - 1;
  sigma = std::sqrt(sigma);
  return std::make_tuple(average, sigma);
}

template <class It, class UnaryFunc>
std::tuple<double, double> aveAndStdev(It first, It last, UnaryFunc selector) {
  return aveAndStdev(first, last, selector, [](auto &e) { return true; });
}

template <class It> std::tuple<double, double> aveAndStdev(It first, It last) {
  return aveAndStdev(first, last, [](auto &e) { return e; });
}

} // place

double sigmoidWeight(double seen, double expected);

namespace std {
template <> struct hash<place::posInfo> {
  static constexpr double A = 1.6180339887498948482 * 1e5;
  hash<double> h;
  size_t operator()(const place::posInfo &e) const;
};
} // std

cv::Vec3b randomColor();

#endif // SCAN_TYPEDEFS_HPP
