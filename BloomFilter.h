//
// Created by loreb on 01/04/2023.
//

#ifndef BLOOMFILTER_OMP_BLOOMFILTER_H
#define BLOOMFILTER_OMP_BLOOMFILTER_H


#include <bitset>

class BloomFilter {
public:
    BloomFilter(int n);
    bool filter_email();
    bool filter_email2();

private:
    double fpr = 0.01;
    int size;
    std::bitset<10> array;
};


#endif //BLOOMFILTER_OMP_BLOOMFILTER_H
