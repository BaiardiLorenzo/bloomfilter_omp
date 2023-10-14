#ifndef BLOOMFILTER_OMP_TEST_H
#define BLOOMFILTER_OMP_TEST_H

#include <vector>

#define SETUP_FILENAME "../results/csv/setup.csv"
#define FILTER_FILENAME "../results/csv/filter.csv"


// GENERATE EMAILS
#define GENERATE_EMAILS false

// NUMBER OF EMAILS TO TEST
#define N_EMAILS 1000000
#define N_SPAM_EMAILS 100000

// TESTS PARAMETERS
#define N_TESTS 3
#define START_TEST 10000

// TEST FPR
#define TEST_FPR 10000

// BLOOM FILTER FILTER PARAMETERS
#define FPR 0.01

#endif //BLOOMFILTER_OMP_TEST_H
