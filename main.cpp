#include <iostream>
#include "EmailGenerator.h"
#include "BloomFilter.h"

#define N_MAILS 1000

int main() {
    std::string emails[N_MAILS];
    EmailGenerator eg = EmailGenerator();
    for(auto & email : emails)
        email = eg.generateEmail();
    std::string newProbablySpamEmail = eg.generateEmail();
    BloomFilter bf = BloomFilter(1000, emails, N_MAILS);
    bool isSpam = bf.filter(newProbablySpamEmail);
    std::cout<<isSpam<<std::endl;
    return 0;
}
