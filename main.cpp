#include <iostream>
#include "EmailGenerator.h"

#define N_MAILS 1000

int main() {
    std::string emails[N_MAILS];
    EmailGenerator eg = EmailGenerator();
    for(auto & email : emails)
        email = eg.generateEmail();
    return 0;
}
