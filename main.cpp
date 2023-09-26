#include <fstream>
#include <vector>
#include "BloomFilter.h"

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
    std::vector<std::size_t> testEmails = {10000, 100000, 1000000};

    std::ofstream outfile;
    std::string fileName = "../test.csv";
    outfile.open(fileName);
    if(outfile.is_open())
        outfile << "THREADS;SPEEDUP;TEST;SEQ;PAR\n";
    outfile.close();

    for (int i=2; i<=omp_get_num_procs(); i*=2) {
        // SET NUMBER OF THREADS
        omp_set_num_threads(i);
        printf("TEST with Core/Threads: %d\n", i);
        for (auto test: testEmails) {
            printf("TEST: %llu\n", test);
            auto *emails = new std::string[test];
            importEmail(emails, test);
            BloomFilter bf = BloomFilter(100000000);
            // SEQUENTIAL SETUP
            double tSeq = bf.setup(emails, test);

            // RESET BLOOM FILTER
            bf.reset();

            // PARALLEL SETUP
            double tPar = bf.setupPar(emails, test);

            double speedUp = tSeq / tPar;
            printf("SPEEDUP TEST %llu: %f \n\n", test, speedUp);

            // WRITE TO TEXT
            outfile.open(fileName, std::ios::out | std::ios::app);
            if (outfile.is_open())
                outfile << i << ";" << speedUp << ";" << test << ";" << tSeq << ";" << tPar << "\n";
            outfile.close();

            //bool isSpam = bf.filter(newProbablySpamEmail);
            //std::cout<<isSpam<<std::endl;

            delete[] emails;
        }
    }
    return 0;
}


