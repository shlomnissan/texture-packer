cmake_minimum_required(VERSION 3.10.2)
project(texture_packer)

set(CMAKE_CXX_STANDARD 17)

set(FREEIMAGE_LIBRARY /usr/lib/x86_64-linux-gnu/libfreeimage.so)

add_executable(texture_packer src/main.cpp src/bitmap.cc src/bitmap.h)

target_link_libraries(texture_packer ${FREEIMAGE_LIBRARY})