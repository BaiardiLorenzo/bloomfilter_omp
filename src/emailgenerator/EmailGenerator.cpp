#include "EmailGenerator.h"

std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));

std::string* EmailGenerator::importEmails(const char* filename, std::size_t nEmails){
    auto emails = new std::string[nEmails];
    std::ifstream infile;
    infile.open(filename);
    for(std::size_t i=0; i<nEmails; i++)
        std::getline(infile, emails[i]);
    infile.close();
    return emails;
}

std::string EmailGenerator::generateRandomEmail(bool spam) {
    std::uniform_int_distribution<int> lengthDist(5, 40);
    int nameLength = lengthDist(gen);
    std::string randomName;
    for (int i = 0; i < nameLength; i++) {
        std::uniform_int_distribution<int> charDist(0, characters.size() - 1);
        randomName += characters[charDist(gen)];
    }
    std::uniform_int_distribution<int> domainDist(0, domains.size() - 1);
    std::uniform_int_distribution<int> urlDist(0, urls.size() - 1);
    if(spam)
        return "SPAM" + randomName +"@"+ domains[domainDist(gen)] + "." + urls[urlDist(gen)];
    else
        return randomName +"@"+ domains[domainDist(gen)] + "." + urls[urlDist(gen)];
}

void EmailGenerator::generateEmails() {
    std::ofstream outfile;
    outfile.open(EMAILS_FILENAME);
    if(outfile.is_open())
        for(int i=0; i<N_EMAILS; i++)
            outfile << generateRandomEmail() << "\n";
    outfile.close();

    outfile.open(SPAMS_FILENAME);
    if(outfile.is_open())
        for(int i=0; i<N_SPAM_EMAILS; i++)
            outfile << generateRandomEmail(true) << "\n";
    outfile.close();
}




