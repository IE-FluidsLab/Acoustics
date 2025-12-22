#!/bin/bash

echo "running example: `date`"
currentdir=`pwd`

# sets up directory structure in current example directory
echo
echo "   setting up example..."
echo

# checks if executables were compiled and available
#if [ ! -e ../../../bin/xspecfem3D ]; then
  #echo "Please compile first all binaries in the root directory, before running this example..."; echo
 # exit 1
#fi

# cleans output files
mkdir -p OUTPUT_FILES
rm -rf OUTPUT_FILES/*


# get the number of processors, ignoring comments in the Par_file
NPROC=`grep ^NPROC DATA/Par_file | grep -v -E '^[[:space:]]*#' | cut -d = -f 2`

BASEMPIDIR=`grep ^LOCAL_PATH DATA/Par_file | cut -d = -f 2 `
mkdir -p $BASEMPIDIR

# decomposes mesh using the pre-saved mesh files in MESH-default (serial running)
echo
echo "  decomposing mesh..."
echo
./xdecompose_mesh $NPROC ./MESH/ $BASEMPIDIR
# checks exit code
if [[ $? -ne 0 ]]; then exit 1; fi

# runs database generation

  echo
  echo "  running database generation on $NPROC processors..."
  echo
  mpirun -np $NPROC ./xgenerate_databases
# checks exit code
if [[ $? -ne 0 ]]; then exit 1; fi

# runs simulation
  # This is a MPI simulation
  echo
  echo "  running solver on $NPROC processors..."
  echo
  mpirun -np $NPROC ./xspecfem3D
# checks exit code
if [[ $? -ne 0 ]]; then exit 1; fi

echo
echo "see results in directory: OUTPUT_FILES/"
echo
echo "done"
echo `date`


