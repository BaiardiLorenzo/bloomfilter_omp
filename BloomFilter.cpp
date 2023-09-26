#include "BloomFilter.h"

BloomFilter::BloomFilter(std::size_t n) : size(n){
    assert(size > 0);
    this->bits = new bool[size];
    reset();
}

void BloomFilter::reset() {
    this->numHashes = 0;
#pragma omp parallel for default(none)
    for(std::size_t i=0; i<size; i++)
        this->bits[i] = false;
}

double BloomFilter::setup(std::string emails[], std::size_t nEmails) {
    this->numHashes = calculateNumHashes(this->size, nEmails);
    double start = omp_get_wtime();
    for(std::size_t i=0; i<nEmails; i++){
        MultiHashes mh(this->size, emails[i]);
        for(std::size_t j=0; j<numHashes; j++)
            this->bits[mh()] = true;
    }
    double time = omp_get_wtime() - start;
    printf("Time setup sequential: %f\n", time);
    return time;
}

double BloomFilter::parallelSetup(std::string emails[], std::size_t nEmails) {
    this->numHashes = calculateNumHashes(this->size, nEmails);
    double start = omp_get_wtime();
#pragma omp parallel for default(none) shared(bits, emails) firstprivate(nEmails, numHashes)
    for(std::size_t i=0; i<nEmails; i++){
        MultiHashes mh(this->size, emails[i]);
        for(std::size_t j=0; j<numHashes; j++)
            this->bits[mh()] = true;
    }
    double time = omp_get_wtime() - start;
    printf("Time setup parallel: %f\n", time);
    return time;
}

int BloomFilter::filterAll(std::string emails[], size_t nEmails) {
    int error = 0;
#pragma omp parallel for default(none) shared(emails, error) firstprivate(nEmails)
    for(std::size_t i=0; i<nEmails; i++)
        if(filter(emails[i])) {
            printf("Email ERROR VALID\n");
            error++;
        }
    printf("\n");
    return error;
}

bool BloomFilter::filter(const std::string& email) {
    MultiHashes mh(this->size, email);
    for(std::size_t i=0; i<numHashes; i++)
        if(!this->bits[mh()]) return false; // SPAM = 0
    return true; // VALID = 1
}

void BloomFilter::seeBits() {
    for(std::size_t i=0;i<1000;i++)
        printf("%d", bits[i]);
    printf("\n");
}

std::size_t BloomFilter::calculateNumHashes(std::size_t n, std::size_t k) {
    return ceil(n/k * log(2));
}

BloomFilter::~BloomFilter() {
    delete[] this->bits;
}











