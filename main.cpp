#include <iostream>
#include "EmailGenerator.h"
#include "BloomFilter.h"

#define N_MAILS 1000

int main() {
    std::string emails[N_MAILS];
    EmailGenerator eg = EmailGenerator();
    for(auto & email : emails)
        email = eg.generateEmail();
    //@TODO CHANGE STD::VECTOR TO ARRAY
    BloomFilter bf = BloomFilter(10000, std::vector<std::string>{emails});
    std::string newProbablySpamEmail = eg.generateEmail();
    bool isSpam = bf.filter(newProbablySpamEmail);
    std::cout<<isSpam<<std::endl;
     return 0;
}
