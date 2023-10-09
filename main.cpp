#include "src/bloomfilter/BloomFilter.h"
#include "src/emailgenerator/EmailGenerator.h"
#include "test.h"
#include <fstream>
#include <map>


void headerResults(int nThreads){
    std::ofstream outfile;
    outfile.open(RESULTS_FILENAME);
    if(outfile.is_open())
        outfile << "test;tSeq;";
    for(int i=2; i<=nThreads; i+=2)
        outfile << "tPar" << i << ";speedUp" << i << ";";
    outfile << "errors\n";
}

void exportResults(std::size_t test, double tSeq, const std::map<std::string, double>& tPars, std::map<std::string, double> speedUps, int errors, double fpr){
    std::ofstream outfile;
    outfile.open(RESULTS_FILENAME, std::ios_base::app);
    if(outfile.is_open())
        for(auto &tPar: tPars)
            outfile << test << ";" << tSeq << ";" << tPar.second << ";" << speedUps[tPar.first] << errors << ";" << fpr << "\n";
    outfile.close();
}

std::vector<std::size_t> getTests(int nTest){
    std::vector<std::size_t> tests;
    int start = START_TEST;
    int end = END_TEST;
    int diff = end - start;
    int increment = diff / (nTest - 1);
    for (int i = 0; i < nTest; i++)
        tests.push_back(start + i * increment);
    return tests;
}

int main() {
#ifdef _OPENMP
    printf("**Number of cores/threads: %d**\n", omp_get_num_procs());
    omp_set_dynamic(0);
#endif
    EmailGenerator eg = EmailGenerator();
    eg.generateEmails();
    headerResults(omp_get_num_procs());
    // TESTS PARAMETERS
    auto tests = getTests(N_TESTS);
    for (auto test: tests) {
        printf("TEST: %llu\n", test);

        // IMPORT EMAILS FROM TXT FILE
        auto emails = EmailGenerator::importEmails(EMAILS_FILENAME, test);

        // INITIALIZATION OF BLOOM FILTER
        BloomFilter bf = BloomFilter();

        // TIME SEQUENTIAL SETUP
        double tSeq = bf.setup(emails, test);
        printf("Sequential time: %f\n", tSeq);

        std::map<std::string, double> tPars;
        std::map<std::string, double> speedUps;
        for (int i=2; i<=omp_get_num_procs(); i+=2) {
            omp_set_num_threads(i);

            // TIME PARALLEL SETUP
            double tPar = bf.parallelSetup(emails, test);
            tPars.insert(std::pair<std::string, double>(std::to_string(i), tPar));
            printf("Parallel time with %d threads: %f\n", i, tPar);

            // SPEEDUP
            double speedUp = tSeq / tPar;
            speedUps.insert(std::pair<std::string, double>(std::to_string(i), speedUp));
            printf("Speedup with %d threads: %f\n", i, speedUp);
        }

        // TESTING SPAM EMAIL
        auto spamEmails = EmailGenerator::importEmails(SPAMS_FILENAME, N_SPAM_EMAILS);
        int errors = bf.filterAll(spamEmails, N_SPAM_EMAILS);
        double fpr = (double)errors / N_SPAM_EMAILS;
        printf("Errors: %d with FPR: %f\n\n", errors, fpr);

        // WRITE RESULT
        exportResults(test, tSeq, tPars, speedUps, errors, fpr);

        // DELETE ARRAY DYNAMIC ALLOCATED
        delete[] emails;
        delete[] spamEmails;
    }
    return 0;
}


