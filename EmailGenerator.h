//
// Created by loreb on 01/04/2023.
//

#ifndef BLOOMFILTER_OMP_EMAILGENERATOR_H
#define BLOOMFILTER_OMP_EMAILGENERATOR_H


#include <string>
#include <iostream>

class EmailGenerator {

public:
    std::string generateEmail();

private:
    constexpr static const char validCharacters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
    constexpr static const char validaNumbers[] = "0123456789";
    std::string urls[3] = {"com", "net", "org"};
    int lenValidCharacter = sizeof(validCharacters) - 1;
    int lenValidNumbers = sizeof(validaNumbers) - 1;

    [[nodiscard]] std::string genUser(int n) const;

    [[nodiscard]] std::string genNum() const;

    [[nodiscard]] std::string genProvider(int n) const;

    std::string genUrl();
};


#endif //BLOOMFILTER_OMP_EMAILGENERATOR_H
