cmake_minimum_required(VERSION 3.10.2)
project(texture_packer)

set(CMAKE_C_COMPILER:FILEPATH /clang_9.0.0/bin/clang)
set(CMAKE_CXX_COMPILER:FILEPATH /clang_9.0.0/bin/clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

set(CMAKE_CXX_STANDARD 17)

set(FREEIMAGE_LIBRARY /usr/lib/x86_64-linux-gnu/libfreeimage.so)

set(HEADER src/bitmap.h
            src/packer.h
            src/metadata.h
            src/rectangle.h)

set(SOURCE src/main.cc
           src/bitmap.cc
           src/packer.cc
           src/metadata.cc)

add_executable(texture_packer ${HEADER} ${SOURCE})

target_link_libraries(texture_packer ${FREEIMAGE_LIBRARY})