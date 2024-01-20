#ifndef BLOOMFILTER_OMP_BLOOMFILTER_H
#define BLOOMFILTER_OMP_BLOOMFILTER_H

#include <bitset>
#include <vector>
#include <cmath>
#include <cassert>
#include <omp.h>
#include "../multihashes/MultiHashes.h"
#include "../../test.h"

class BloomFilter {
public:
    explicit BloomFilter(double fpr=FPR);
    ~BloomFilter();
    bool *getBits() const;
    double sequentialSetup(std::string items[], std::size_t nItems);
    double parallelSetup(std::string items[], std::size_t nItems);
    int sequentialFilterAll(std::string items[], size_t nItems);
    int parallelFilterAll1(std::string items[], size_t nItems);
    int parallelFilterAll2(std::string items[], size_t nItems);

private:
    double fpr;
    std::size_t size;
    std::size_t nHashes;
    bool* bits;

    bool filter(const std::string& email);
    void initialize(std::size_t nItems);
    void add(const std::string &items);
    void reset();
};


#endif //BLOOMFILTER_OMP_BLOOMFILTER_H
