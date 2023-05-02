#include <iostream>
#include "EmailGenerator.h"
#include "BloomFilter.h"

#define N_MAILS 1000

int main() {
    std::string emails[N_MAILS];
    EmailGenerator eg = EmailGenerator();
    for(auto & email : emails)
        email = eg.generateEmail();

    //BLOOM FILTER
    //BloomFilter bf = BloomFilter(1000, emails);
    return 0;
}
