//
// Created by loreb on 01/04/2023.
//

#include "EmailGenerator.h"


std::string EmailGenerator::generateEmail() {
    std::string email;
    email.append(genUser(rand()));
    email.append(genNum());
    email.append("@");
    email.append(genProvider(rand()));
    email.append(genUrl());
    return email;
}

std::string EmailGenerator::genUser(int n) const {
    std::string user;
    for(int i = 1; i < n; i++)
        user.push_back(validCharacters[rand() % lenValidCharacter]);
    return user;
}

std::string EmailGenerator::genNum() const{
    std::string num;
    num.push_back(validaNumbers[rand() % lenValidNumbers]);
    return num;
}

std::string EmailGenerator::genProvider(int n) const {
    std::string provide;
    for(int i = 0; i < n; i++)
        provide.push_back(validCharacters[rand() % lenValidCharacter]);
    return provide;
}

std::string EmailGenerator::genUrl(){
    std::string url = urls[rand() % sizeof(urls)];
    return url;
}


