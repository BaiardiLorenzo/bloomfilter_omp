//
// Created by loreb on 01/04/2023.
//

#ifndef BLOOMFILTER_OMP_BLOOMFILTER_H
#define BLOOMFILTER_OMP_BLOOMFILTER_H


#include <bitset>
#include <vector>

class BloomFilter {
public:
    explicit BloomFilter(std::size_t size, const std::vector<std::string>& emails);
    void filterAll(const std::vector<std::string>& emails);
    bool filter(const std::string& email);


private:
    std::size_t size;
    std::size_t numHashes;
    std::vector<bool> bits;

    void setup(std::size_t numHashes, const std::vector<std::string>& set);

};


#endif //BLOOMFILTER_OMP_BLOOMFILTER_H
