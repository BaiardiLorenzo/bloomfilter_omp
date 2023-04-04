//
// Created by loreb on 01/04/2023.
//

#include "BloomFilter.h"

BloomFilter::BloomFilter(std::string spamEmails[], int size) {
    for(int i=0;i<size;i++){
        setSpamEmail(spamEmails[i]);
    }
}

void BloomFilter::setSpamEmail(std::string email) {
    if (checkSpamEmail(email)) {
        std::cout << email << " is Probably already present" << std::endl;
    }
    else{
        /*
        int a = h1(s, arrSize);
        int b = h2(s, arrSize);
        int c = h3(s, arrSize);
        int d = h4(s, arrSize);

        bitarray[a] = true;
        bitarray[b] = true;
        bitarray = true;
        bitarray[d] = true;
        */
        //PLACEHOLDER
        //FUNCTION MULTIPLY HAS
        bitarray[0] = true;
        std::cout<<email<<"inserted"<<std::endl;
    }
}

bool BloomFilter::checkSpamEmail(std::string email) {
    /* HASH FUNCTION EXAMPLES
    int a = h1(s, arrSize);
    int b = h2(s, arrSize);
    int c = h3(s, arrSize);
    int d = h4(s, arrSize);
    */

    if (true) //CHECK VALUES INSIDE HASH (bitarray[a] && bitarray[b] && bitarray[c]&& bitarray[d])
        return true;
    else
        return false;

}
