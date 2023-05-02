//
// Created by loreb on 01/04/2023.
//

#ifndef BLOOMFILTER_OMP_BLOOMFILTER_H
#define BLOOMFILTER_OMP_BLOOMFILTER_H


#include <bitset>
#include <vector>

class BloomFilter {
public:
    explicit BloomFilter(int n, const std::vector<std::string>& emails);
    void filterAll(const std::vector<std::string>& emails);
    bool filter(const std::string& email);


private:
    int size;
    std::vector<bool> array;
    //@TODO std::vector<function> hashes;

    void setup(const std::vector<std::string>& set);
    void setHashes(int n);

};


#endif //BLOOMFILTER_OMP_BLOOMFILTER_H
