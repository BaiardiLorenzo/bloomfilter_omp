#ifndef BLOOMFILTER_OMP_MULTIHASHES_H
#define BLOOMFILTER_OMP_MULTIHASHES_H


#include <cstddef>
#include <string>
#include <random>
#include <cassert>

class MultiHashes {
public:
    explicit MultiHashes(std::size_t size, const std::string& email);
    std::size_t operator() ();

private:
    std::size_t size;
    std::mt19937 rand;
};


#endif //BLOOMFILTER_OMP_MULTIHASHES_H
