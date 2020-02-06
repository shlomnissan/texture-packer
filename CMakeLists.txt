cmake_minimum_required(VERSION 3.10.2)
project(texture_packer)

set(CMAKE_CXX_STANDARD 17)

set(FREEIMAGE_LIBRARY /usr/lib/x86_64-linux-gnu/libfreeimage.so)

link_libraries(stdc++fs)

add_executable(texture_packer src/main.cpp
                              src/bitmap.cc
                              src/bitmap.h
                              src/packer.cc
                              src/packer.h
                              src/node.h
                              src/metadata.cc
                              src/metadata.h
                              src/rectangle.h)

target_link_libraries(texture_packer ${FREEIMAGE_LIBRARY})