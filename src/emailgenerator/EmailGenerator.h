#ifndef BLOOMFILTER_OMP_EMAILGENERATOR_H
#define BLOOMFILTER_OMP_EMAILGENERATOR_H

#include "../../test.h"

#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

#define EMAILS_FILENAME "../dataset/emails.txt"
#define SPAMS_FILENAME "../dataset/spams.txt"

// NUMBER OF EMAILS TO TEST
#define N_EMAILS 10000000
#define N_SPAM_EMAILS 100000

class EmailGenerator {

public:
    void generateEmails();
    static std::string* importEmails(const char* filename, std::size_t nEmails);

private:
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.";
    std::vector<std::string> domains = {"gmail", "yahoo", "hotmail", "libero", "icloud", "outlook", "protonmail", "alice",
                                        "tiscali", "fastweb", "virgilio", "tim", "vodafone", "wind", "telecom", "poste"};
    std::vector<std::string> urls = {"com", "net", "org", "info", "it", "eu", "biz", "gov", "edu", "co.uk",
                                        "de", "fr", "es"};
    std::string generateRandomEmail(bool spam=false);

};


#endif //BLOOMFILTER_OMP_EMAILGENERATOR_H
