//
// Created by loreb on 01/04/2023.
//

#include <cmath>
#include <cassert>
#include "BloomFilter.h"
#include "MultiHashes.h"

BloomFilter::BloomFilter(std::size_t n, const std::vector<std::string>& emails) : size(n), bits(n){
    assert(size > 0);
    this->numHashes = (size/emails.size()) * log(2);
    setup(numHashes, emails);
}

void BloomFilter::setup(std::size_t numHashes, const std::vector<std::string>& emails) {
    for(auto &email: emails){
        MultiHashes mh(this->size, email);
        for(std::size_t i=0;i<numHashes;i++)
            this->bits[mh()] = true;
    }
}

void BloomFilter::filterAll(const std::vector<std::string>& emails) {
    for(const auto& email: emails)
        printf("Email valida: %b", filter(email));
}

bool BloomFilter::filter(const std::string& email) {
    MultiHashes mh(this->size, email);
    for(std::size_t i=0;i<numHashes;i++)
        if(!this->bits[mh()]) return false;
    return true;
}




