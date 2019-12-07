set (CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 2.8)
project( Sequential )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( Sequential /home/jahoon.koo/Jahoon/CSCI4551/Final/sequential.cpp )
target_link_libraries( Sequential ${OpenCV_LIBS} )

