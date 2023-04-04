//
// Created by loreb on 01/04/2023.
//

#ifndef BLOOMFILTER_OMP_BLOOMFILTER_H
#define BLOOMFILTER_OMP_BLOOMFILTER_H

#include <iostream>

#define FILTER_SIZE 1000

class BloomFilter {
public:
    BloomFilter(std::string spamEmails[], int size);

    bool checkSpamEmail(std::string email);

private:
    bool bitarray[FILTER_SIZE] = {false};

    void setSpamEmail(std::string email);

};


#endif //BLOOMFILTER_OMP_BLOOMFILTER_H
