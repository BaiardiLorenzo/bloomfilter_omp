
#include <fstream>
#include <vector>
#include "BloomFilter.h"
#include "BloomFilterPar.h"

void importEmail(std::string emails[], std::size_t nEmails){
    std::ifstream infile;
    std::string fileName = "../dataset/emails_"+std::to_string(nEmails)+".txt";
    infile.open(fileName);
    for(int i=0; i<nEmails; i++)
        std::getline(infile, emails[i]);
    infile.close();
}

int main() {
#ifdef _OPENMP
    printf("Core/Threads: %d\n", omp_get_num_procs());
    omp_set_dynamic(0);
#endif
    std::vector<std::size_t> testPlanes = {10000, 100000, 1000000};
    for(auto nEmails: testPlanes){
        auto* emails = new std::string[nEmails];
        importEmail(emails, nEmails);
        BloomFilter bf = BloomFilter(100000000, emails, nEmails);
        //BloomFilterPar bfp = BloomFilterPar(100000000, emails, nEmails);
        //bool isSpam = bf.filter(newProbablySpamEmail);
        //std::cout<<isSpam<<std::endl;
        delete[] emails;
    }
    return 0;
}


