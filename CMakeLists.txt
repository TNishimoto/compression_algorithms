cmake_minimum_required(VERSION 2.8)

project(compression_algorithms CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CPP_STATIC)
set(CMAKE_CXX_FLAGS "-m64 -Wall -Wextra -static")
else(CPP_STATIC)
set(CMAKE_CXX_FLAGS "-m64 -Wall -Wextra")
endif(CPP_STATIC)

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    message("Release Mode")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG  "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -DNDEBUG")

if(NOT TARGET libdivsufsort)
include_directories(${CMAKE_BINARY_DIR}/modules/libdivsufsort/include)
add_subdirectory(modules/libdivsufsort)
endif()

INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(modules)


#### Modules
#libdivsufsort directory is here.
#Please modify it appropriately.
LINK_DIRECTORIES(~/lib)
INCLUDE_DIRECTORIES(~/include)


add_executable(lz_compress.out main/lz_compress_main.cpp)
target_link_libraries(lz_compress.out divsufsort divsufsort64)

#add_executable(decompress.out main/decompress_main.cpp)
#add_executable(rev.out rev_main.cpp)
add_executable(delta.out main/delta_main.cpp)
target_link_libraries(delta.out divsufsort divsufsort64)


#target_link_libraries(compress.out fn)
#target_link_libraries(decompress.out fn)
#target_link_libraries(rev.out fn)


