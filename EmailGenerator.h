//
// Created by loreb on 01/04/2023.
//

#ifndef BLOOMFILTER_OMP_EMAILGENERATOR_H
#define BLOOMFILTER_OMP_EMAILGENERATOR_H


#include <string>
#include <iostream>

#define MAX_USER_LENGHT 15
#define N_DOMAINS 5
#define N_URLS 3

class EmailGenerator {

public:
    std::string generateEmail();

private:
    constexpr static const char validCharacters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz" "0123456789";
    const int lenValidCharacter = sizeof(validCharacters) - 1;
    std::string domains[N_DOMAINS] = {"@gmail", "@yahoo", "@hotmail", "@libero", "@icloud"};
    std::string urls[N_URLS] = {".com", ".net", ".org"};

    [[nodiscard]] std::string genUser() const;

    [[nodiscard]] std::string genDomain() const;

    std::string genUrl();
};


#endif //BLOOMFILTER_OMP_EMAILGENERATOR_H
