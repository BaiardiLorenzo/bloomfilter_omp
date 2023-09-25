cmake_minimum_required(VERSION 3.25)
project(bloomfilter_omp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fopenmp")

find_package(OpenMP REQUIRED)

add_executable(bloomfilter_omp main.cpp BloomFilter.cpp BloomFilter.h MultiHashes.cpp MultiHashes.h MultiHashes.h
        BloomFilterPar.cpp
        BloomFilterPar.h)

target_link_libraries(bloomfilter_omp OpenMP::OpenMP_CXX)