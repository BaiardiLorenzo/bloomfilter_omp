cmake_minimum_required(VERSION 3.24.2)
project(bloomfilter_omp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -fopenmp")

find_package(OpenMP REQUIRED)

add_executable(bloomfilter_omp main.cpp
        src/bloomfilter/BloomFilter.cpp
        src/bloomfilter/BloomFilter.h
        src/multihashes/MultiHashes.cpp
        src/multihashes/MultiHashes.h
        src/multihashes/MultiHashes.h
        src/emailgenerator/EmailGenerator.cpp
        src/emailgenerator/EmailGenerator.h
        test.h)

target_link_libraries(bloomfilter_omp OpenMP::OpenMP_CXX)