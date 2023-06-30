//
// Created by loreb on 01/04/2023.
//

#include <iostream>
#include <cmath>
#include <cassert>
#include "BloomFilter.h"
#include "MultiHashes.h"

BloomFilter::BloomFilter(std::size_t n, std::string emails[], std::size_t nEmails) : size(n), bitset(size){
    assert(size > 0);
    this->numHashes = size/nEmails * log(2);
    setup(emails, nEmails);
}

void BloomFilter::setup(std::string emails[], std::size_t nEmails) {
    for(std::size_t i=0; i<nEmails; i++){
        MultiHashes mh(this->size, emails[i]);
        for(std::size_t j=0; j<numHashes; j++)
            this->bitset[mh()] = true;
    }
    //for (int i = 0; i < size; i++)
    //    std::cout << bitset[i];
}

bool* BloomFilter::filterAll(std::string emails[], std::size_t nEmails) {
    auto result = new bool[nEmails];
    for(std::size_t i=0; i<nEmails; i++)
        result[i] = filter(emails[i]);
    return result;
}

bool BloomFilter::filter(const std::string& email) {
    MultiHashes mh(this->size, email);
    for(std::size_t i=0; i<numHashes; i++) {
        bool c = this->bitset[mh()];
        if (!c) return false;
    }
    return true;
}




