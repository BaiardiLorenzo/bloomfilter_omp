cmake_minimum_required(VERSION 3.24.2)
project(bloomfilter_omp)

set(CMAKE_CXX_STANDARD 17)

add_executable(bloomfilter_omp main.cpp BloomFilter.cpp BloomFilter.h EmailGenerator.cpp EmailGenerator.h MultiHashes.cpp MultiHashes.h MultiHashes.h)
