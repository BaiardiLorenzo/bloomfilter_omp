#ifndef BLOOMFILTER_OMP_BLOOMFILTER_H
#define BLOOMFILTER_OMP_BLOOMFILTER_H

#include <bitset>
#include <vector>
#include <cmath>
#include <cassert>
#include <omp.h>
#include "MultiHashes.h"

class BloomFilter {
public:
    explicit BloomFilter(std::size_t size);
    ~BloomFilter();
    int filterAll(std::string emails[], size_t nEmails);
    double setup(std::string emails[], std::size_t nEmails);
    double parallelSetup(std::string emails[], std::size_t nEmails);
    void seeBits();
    void reset();

private:
    std::size_t size;
    std::size_t numHashes{};
    bool* bits;

    bool filter(const std::string& email);
    static std::size_t calculateNumHashes(std::size_t n, std::size_t k);
};


#endif //BLOOMFILTER_OMP_BLOOMFILTER_H
