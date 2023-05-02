//
// Created by loreb on 01/04/2023.
//

#include "EmailGenerator.h"


std::string EmailGenerator::generateEmail() {
    std::string email;
    email.append(genUser());
    email.append(genDomain());
    email.append(genUrl());
    return email;
}

std::string EmailGenerator::genUser() const {
    std::string user;
    for(int i = 1; i < MAX_USER_LENGHT; i++)
        user.push_back(validCharacters[std::rand() % lenValidCharacter]);
    return user;
}

std::string EmailGenerator::genDomain() const {
    return domains[std::rand() % N_DOMAINS];
}

std::string EmailGenerator::genUrl(){
    return urls[std::rand() % N_URLS];
}


