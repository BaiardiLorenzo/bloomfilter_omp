#include "src/bloomfilter/BloomFilter.h"
#include "src/emailgenerator/EmailGenerator.h"
#include "test.h"
#include <fstream>
#include <map>
#include <iomanip>


void headerResults(const std::string& filename, int nThreads){
    std::ofstream outfile;
    outfile.open(filename);
    if(outfile.is_open())
        outfile << "test;tSeq;";
    for(int i=2; i<=nThreads; i+=2)
        outfile << "tPar" << i << ";speedUp" << i << ";";
    outfile << "fpr;\n";
}

void exportResults(const std::string& filename, std::size_t test, double tSeq, const std::map<std::size_t, double>& tPars,
                   std::map<std::size_t,double> speedUps, double fpr){
    std::ofstream outfile;
    outfile.open(filename, std::ios_base::app);
    if(outfile.is_open()){
        outfile << std::fixed << std::setprecision(3);
        outfile << test << ";" << tSeq << ";";
        for(auto tPar: tPars)
            outfile << tPar.second << ";" << speedUps[tPar.first] << ";";
        outfile << fpr << ";\n";
    }
}

std::vector<std::size_t> getTests(int nTest, int start, int end){
    std::vector<std::size_t> tests;
    int diff = end - start;
    int increment = diff / (nTest - 1);
    for (int i = 0; i < nTest; i++)
        tests.push_back(start + i * increment);
    return tests;
}

void testSetup(BloomFilter bf) {
    printf("TEST SETUP\n");
    headerResults(SETUP_FILENAME, omp_get_num_procs());
    auto tests = getTests(N_TESTS, START_TEST, 10000);
    for (auto test: tests) {
        printf("TEST: %llu\n", test);

        // IMPORT EMAILS FROM TXT FILE
        auto emails = EmailGenerator::importEmails(EMAILS_FILENAME, test);

        // TIME SEQUENTIAL SETUP
        double tSeq = bf.sequentialSetup(emails, test);
        printf("Sequential time: %f\n", tSeq);

        bool* seq_bits = bf.getBits();

        std::map<std::size_t, double> tPars;
        std::map<std::size_t, double> speedUps;
        for (int i=2; i<=omp_get_num_procs(); i+=2) {
            omp_set_num_threads(i);

            // TIME PARALLEL SETUP
            double tPar = bf.parallelSetup(emails, test);
            tPars.insert(std::pair<std::size_t, double>(i, tPar));
            printf("Parallel time with %d threads: %f\n", i, tPar);

            bool* par_bits = bf.getBits();

            // SPEEDUP
            double speedUp = tSeq / tPar;
            speedUps.insert(std::pair<std::size_t, double>(i, speedUp));
            printf("Speedup with %d threads: %f\n", i, speedUp);

            // CHEKING ARRAYS
            if(*seq_bits != *par_bits)
                printf("******ERROR: BIT_Arrays are not equal\n");
        }

        // DELETE ARRAY DYNAMIC ALLOCATED
        delete[] emails;


        // FPR FILTER TEST
        auto fprSpamEmails = EmailGenerator::importEmails(SPAMS_FILENAME, TEST_FPR);
        int errors = bf.parallelFilterAll1(fprSpamEmails, TEST_FPR);
        double fpr = (double)errors / TEST_FPR;
        printf("Errors: %d with FPR: %f\n\n", errors, fpr);

        // DELETE ARRAY DYNAMIC ALLOCATED
        delete[] fprSpamEmails;

        // WRITE RESULT
        exportResults(SETUP_FILENAME, test, tSeq, tPars, speedUps, fpr);
    }
}

void testFiltering(BloomFilter bf){
    printf("TEST FILTER\n");
    headerResults(FILTER_FILENAME, omp_get_num_procs());
    auto emails = EmailGenerator::importEmails(EMAILS_FILENAME, N_EMAILS);
    bf.sequentialSetup(emails, 10000);

    auto tests = getTests(N_TESTS, START_TEST, N_SPAM_EMAILS);
    for (auto test: tests) {
        printf("TEST: %llu\n", test);

        // IMPORT EMAILS FROM TXT FILE
        auto spamEmails = EmailGenerator::importEmails(SPAMS_FILENAME, test);

        // TIME SEQUENTIAL FILTER
        auto start = omp_get_wtime();
        int seqErrors = bf.sequentialFilterAll(spamEmails, test);
        auto tSeq = omp_get_wtime() - start;
        printf("Sequential time filter: %f\n", tSeq);

        std::map<std::size_t, double> tPars;
        std::map<std::size_t, double> speedUps;
        for (int i=2; i<=omp_get_num_procs(); i+=2) {
            omp_set_num_threads(i);

            // TIME PARALLEL FILTER
            start = omp_get_wtime();
            int parErrors = bf.parallelFilterAll1(spamEmails, test);
            auto tPar = omp_get_wtime() - start;
            tPars.insert(std::pair<std::size_t, double>(i, tPar));
            printf("Parallel time filter with %d threads: %f\n", i, tPar);

            // CHECKING ERRORS
            if (seqErrors != parErrors)
                printf("******ERROR: sequential errors: %d, parallel errors: %d\n", seqErrors, parErrors);

            // SPEEDUP
            double speedUp = tSeq / tPar;
            speedUps.insert(std::pair<std::size_t, double>(i, speedUp));
            printf("Speedup filter with %d threads: %f\n", i, speedUp);
        }
        // DELETE ARRAY DYNAMIC ALLOCATED
        delete[] spamEmails;

        // FPR
        double fpr = (double)seqErrors / (double)test;
        printf("Errors: %d with FPR: %f\n\n", seqErrors, fpr);

        // WRITE RESULT
        exportResults(FILTER_FILENAME, test, tSeq, tPars, speedUps, fpr);
    }
}

int main() {
#ifdef _OPENMP
    printf("**Number of cores/threads: %d**\n", omp_get_num_procs());
    omp_set_dynamic(0);
#endif
    if (GENERATE_EMAILS) {
        printf("Generating emails...\n");
        EmailGenerator eg = EmailGenerator();
        eg.generateEmails();
    }

    // INITIALIZATION OF BLOOM FILTER
    BloomFilter bf = BloomFilter();

    // TESTS SETUP
    testSetup(bf);

    // TESTING FILTERING
    testFiltering(bf);

    return 0;
}


