#include <iostream>
#include "EmailGenerator.h"
#include "BloomFilter.h"

#define N_MAILS 1000
#define N_TEST 200

int main() {
    std::string emails[N_MAILS];
    EmailGenerator eg = EmailGenerator();
    for(auto & email : emails) {
        email = eg.generateEmail();
        std::cout<<email<<std::endl;
    }
    std::string newProbablySpamEmails[N_TEST];
    for(auto & newProbablySpamEmail : newProbablySpamEmails)
        newProbablySpamEmail = eg.generateEmail();

    for (int i = 0; i < N_TEST; i++)
        std::cout << newProbablySpamEmails[i];

    std::string newNoSpamEmail = emails[N_TEST];
    BloomFilter bf = BloomFilter(10000, emails, N_MAILS);
    bool* areSpam;
    areSpam = bf.filterAll(newProbablySpamEmails, N_TEST);
    for (int i = 0; i < N_TEST; i++)
        std::cout << areSpam[i];
    //isSpam = bf.filter(newNoSpamEmail);
    //std::cout<<isSpam<<std::endl;
    return 0;
}
