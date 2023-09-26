#include "BloomFilter.h"
#include <fstream>
#include <vector>

#define TEST_PATH "../test.csv"
#define EMAIL_PATH "../dataset/emails/emails_"
#define SPAM_PATH "../dataset/spam/spam_"

#define HEADER_TEST "THREADS;SPEEDUP;TEST;SEQ;PAR;ERRORS\n"

#define N_BITS 8000000
#define N_SPAM_EMAILS 100


std::string* importEmail(std::size_t nEmails){
    auto emails = new std::string[nEmails];
    std::ifstream infile;
    std::string fileName = EMAIL_PATH+std::to_string(nEmails)+".txt";
    infile.open(fileName);
    for(std::size_t i=0; i<nEmails; i++)
        std::getline(infile, emails[i]);
    infile.close();
    return emails;
}

std::string* importSpam(std::size_t nSpamEmails, std::size_t test){
    auto *emails = new std::string[nSpamEmails];
    std::ifstream infile;
    std::string fileName = SPAM_PATH + std::to_string(test) + "_" + std::to_string(nSpamEmails) + ".txt";
    infile.open(fileName);
    for(std::size_t i=0; i<nSpamEmails; i++)
        std::getline(infile, emails[i]);
    infile.close();
    return emails;
}

void headerResults(){
    std::ofstream outfile;
    outfile.open(TEST_PATH);
    if(outfile.is_open())
        outfile << HEADER_TEST;
    outfile.close();
}

void exportResults(int nThreads, double speedUp, std::size_t test, double tSeq, double tPar, int errors){
    std::ofstream outfile;
    outfile.open(TEST_PATH, std::ios::out | std::ios::app);
    if (outfile.is_open())
        outfile<<nThreads<<";"<<speedUp<<";"<<test<<";"<<tSeq<<";"<<tPar<<";"<<errors<<"\n";
    outfile.close();
}

int main() {
#ifdef _OPENMP
    printf("**Number of cores/threads: %d**\n", omp_get_num_procs());
    omp_set_dynamic(0);
#endif
    headerResults();
    std::vector<std::size_t> testEmails = {1000, 10000, 100000, 1000000};
    for (int i=2; i<=omp_get_num_procs(); i*=2) {
        printf("Number of cores/threads used: %d\n", i);
        omp_set_num_threads(i); // SET NUMBER OF THREADS
        for (auto test: testEmails) {
            printf("TEST: %llu\n", test);

            // IMPORT EMAILS FROM TXT FILE
            auto emails = importEmail(test);

            // INITIALIZATION OF BLOOM FILTER
            BloomFilter bf = BloomFilter(N_BITS);

            // TIME SEQUENTIAL SETUP
            double tSeq = bf.setup(emails, test);

            // RESET BLOOM FILTER
            bf.reset();
            //bf.seeBits();

            // TIME PARALLEL SETUP
            double tPar = bf.setupPar(emails, test);

            double speedUp = tSeq / tPar;
            printf("Speedup: %f\n", speedUp);

            // TESTING SPAM EMAIL
            std::size_t nSpamEmail = N_SPAM_EMAILS;
            auto spamEmails = importSpam(nSpamEmail, test);
            int errors = bf.filterAll(spamEmails, nSpamEmail);

            // WRITE RESULT
            exportResults( i, speedUp, test, tSeq, tPar, errors);

            // DELETE ARRAY DYNAMIC ALLOCATED
            delete[] emails;
            delete[] spamEmails;
        }
    }
    return 0;
}


