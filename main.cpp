#include <iostream>
#include "EmailGenerator.h"
#include "BloomFilter.h"

#define N_MAILS 1000

int main() {
    std::string emails[N_MAILS];
    EmailGenerator eg = EmailGenerator();
    for(auto & email : emails)
        email = eg.generateEmail();
    BloomFilter bf = BloomFilter(emails, N_MAILS);
    std::string newProbablySpamEmail = eg.generateEmail();
    bool isSpam = bf.checkSpamEmail(newProbablySpamEmail);
    std::cout<<isSpam<<std::endl;
    return 0;
}
