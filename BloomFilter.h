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
    explicit BloomFilter(std::size_t size, std::string emails[], std::size_t nEmails);
    ~BloomFilter();
    void filterAll(std::string emails[], std::size_t nEmails);
    bool filter(const std::string& email);

protected:
    std::size_t size;
    std::size_t numHashes;
    bool* bits;

    void setup(std::size_t numHashes, std::string emails[], std::size_t nEmails);
};


#endif //BLOOMFILTER_OMP_BLOOMFILTER_H
