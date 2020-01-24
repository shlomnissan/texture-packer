cmake_minimum_required(VERSION 3.15)
project(texture_packer)

set(CMAKE_CXX_STANDARD 14)

set(FREEIMAGE_INCLUDE_DIR /usr/local/Cellar/freeimage/3.18.0/include)
set(FREEIMAGE_LIBRARY /usr/local/Cellar/freeimage/3.18.0/lib/libfreeimage.a)

include_directories(${FREEIMAGE_INCLUDE_DIR})

add_executable(texture_packer src/main.cpp src/free_image.cc src/free_image.h)

target_link_libraries(texture_packer ${FREEIMAGE_LIBRARY})