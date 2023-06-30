//
// Created by loreb on 01/04/2023.
//

#ifndef BLOOMFILTER_OMP_BLOOMFILTER_H
#define BLOOMFILTER_OMP_BLOOMFILTER_H


#include <bitset>
#include <vector>

class BloomFilter {
public:
    explicit BloomFilter(std::size_t size, std::string emails[], std::size_t nEmails);
    bool* filterAll(std::string emails[], std::size_t nEmails);
    bool filter(const std::string& email);


private:
    std::size_t size;
    std::size_t numHashes;
    std::vector<bool> bitset;

    void setup(std::string emails[], std::size_t nEmails);

};


#endif //BLOOMFILTER_OMP_BLOOMFILTER_H
