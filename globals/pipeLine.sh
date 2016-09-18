#Usage: ./pipeLine.sh <location_of_data_to_use> <location_of_build_dir>
#CSE Scale = 98.0
#DUC Scale = 73.5

#!/bin/bash

#Make all the needed folders
mkdir -p $1/placementOptions/V1
mkdir -p $1/placementOptions/V2
mkdir -p $1/panoramas/images
mkdir -p $1/panoramas/data
mkdir -p $1/cloudNormals
mkdir -p $1/binaryFiles
mkdir -p $1/densityMaps/R3
mkdir -p $1/densityMaps/R0
mkdir -p $1/densityMaps/rotations
mkdir -p $1/densityMaps/R1
mkdir -p $1/densityMaps/R2
mkdir -p $1/densityMaps/zeros
mkdir -p $1/voxelGridcs/R3
mkdir -p $1/voxelGrids/R0
mkdir -p $1/voxelGrids/R1
mkdir -p $1/voxelGrids/R2
mkdir -p $1/voxelGrids/metaData

# Build the project
cd $2
make || exit 1

#run the 3 programs

#echo "Running preprocessor"
#preprocessor=$2/preprocessor/preprocessor
#$preprocessor -dataPath=$1 || exit 1
#
#echo "Running scanDensity"
#scanDensity=$2/scanDensity/scanDensity
#$scanDensity -dataPath=$1 || exit 1
#
#echo "Running placeScan"
#placeScan=$2/placeScan/placeScan
#$placeScan -dataPath=$1 -V1 -noreshow || exit 1

echo "Running joiner"
joiner=$2/joiner/joiner
$joiner -dataPath=$1 -redo || exit 1
