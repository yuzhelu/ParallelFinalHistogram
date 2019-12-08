cmake_minimum_required(VERSION 2.8)
project( MPI_Histogram )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
find_package(MPI)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
add_executable( MPI_Histogram /home/khang.le/csc4551/finalProject/MPI_Histogram5/MPI_Histogram.cpp)
target_link_libraries( MPI_Histogram ${OpenCV_LIBS} ${MPI_C_LIBRARIES})


 
