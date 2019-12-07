cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)
project( CudaImageHistogram )
find_package( OpenCV REQUIRED )
find_package( CUDA REQUIRED )

set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_60,code=sm_60)

include_directories( ${OpenCV_INCLUDE_DIRS} )
cuda_add_executable( CudaImageHistogram /home/jahoon.koo/Jahoon/CSCI4551/Final/CUDA/CUDA.cu )
target_link_libraries( CudaImageHistogram ${OpenCV_LIBS} )

