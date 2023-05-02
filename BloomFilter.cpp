//
// Created by loreb on 01/04/2023.
//

#include "BloomFilter.h"

BloomFilter::BloomFilter(int n, const std::vector<std::string>& emails) : size(n), array(n, false){
    //@TODO SET NUMBER OF HASHES
    //@PYTHON numHashes = int((size / len(set)) * math.log(2))
    //@TODO SET VECTOR OF HASHES FUNCTION
    setHashes(0);
    setup(emails);
}

void BloomFilter::setHashes(int n) {
    //@TODO CREATE HASHES FUNCTION
}

void BloomFilter::setup(const std::vector<std::string>& spamEmails) {
    //TODO SETUP BIT VECTOR
}

void BloomFilter::filterAll(const std::vector<std::string>& emails) {
    for(const auto& email: emails)
        printf("Email valida: %b", filter(email));
}

bool BloomFilter::filter(const std::string& email) {
    /*
       def filter(self, m):
        for hashFun in self.hashes:
            pos = hashFun(m) % len(self.array)
            if self.array[pos] == 0:
                return False
        return True
     */
    return true;
}




