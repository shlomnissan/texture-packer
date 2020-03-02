cmake_minimum_required(VERSION 3.10.2)
project(texture_packer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

set(CMAKE_CXX_STANDARD 17)

# Add dependencies
# ------------------------------------------

set(FREEIMAGE_LIBRARY /usr/lib/x86_64-linux-gnu/libfreeimage.so)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/gflags/CMakeLists.txt)
    add_subdirectory(lib/gflags)
else ()
    message(SEND_ERROR "Run 'git submodule update --init'")
endif ()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest/CMakeLists.txt)
    add_subdirectory(lib/googletest)
else ()
    message(SEND_ERROR "Run 'git submodule update --init'")
endif ()

# Include project files 
# ------------------------------------------

set(HEADER src/bitmap.h
            src/packer.h
            src/metadata.h
            src/rectangle.h)

set(SOURCE src/main.cc
           src/bitmap.cc
           src/packer.cc
           src/metadata.cc)

add_executable(texture_packer ${HEADER} ${SOURCE})

target_link_libraries(texture_packer ${FREEIMAGE_LIBRARY} gflags::gflags)