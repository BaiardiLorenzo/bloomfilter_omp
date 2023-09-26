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

double BloomFilter::setupPar(std::string emails[], std::size_t nEmails) {
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

void BloomFilter::filterAll(std::string emails[], std::size_t nEmails) {
    for(std::size_t i=0; i<nEmails; i++)
        printf("Email valida: %b", filter(emails[i]));
}

void BloomFilter::filterAllPar(std::string *emails, std::size_t nEmails) {
//#pragma omp parallel for default(none) shared(bits)
    for(std::size_t i=0; i<nEmails; i++)
        printf("Email valida: %b", filter(emails[i]));
}

bool BloomFilter::filter(const std::string& email) {
    MultiHashes mh(this->size, email);
    for(std::size_t i=0; i<numHashes; i++)
        if(!this->bits[mh()]) return false;
    return true;
}

std::size_t BloomFilter::calculateNumHashes(std::size_t n, std::size_t k) {
    return ceil(n/k * log(2));
}

BloomFilter::~BloomFilter() {
    delete[] this->bits;
}










