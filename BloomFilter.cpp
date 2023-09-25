#include "BloomFilter.h"


BloomFilter::BloomFilter(std::size_t n, std::string emails[], std::size_t nEmails) : size(n){
    assert(size > 0);
    this->bits = new bool[size];
#pragma omp parallel for default(none)
    for(std::size_t i=0; i<size; i++)
        this->bits[i] = false;
    this->numHashes = ceil(size/nEmails * log(2));
    setup(numHashes, emails, nEmails);
}

BloomFilter::~BloomFilter() {
    delete[] this->bits;
}

void BloomFilter::setup(std::size_t numHashes, std::string emails[], std::size_t nEmails) {
    double start = omp_get_wtime();
//#pragma omp parallel for default(none) shared(bits, emails) firstprivate(nEmails, numHashes)
    for(std::size_t i=0; i<nEmails; i++){
        MultiHashes mh(this->size, emails[i]);
        for(std::size_t j=0; j<numHashes; j++)
            this->bits[mh()] = true;
    }
    double time = omp_get_wtime() - start;
    printf("TIME SETUP SEQ: %f\n", time);
}

void BloomFilter::filterAll(std::string emails[], std::size_t nEmails) {
    for(std::size_t i=0; i<nEmails; i++)
        printf("Email valida: %b", filter(emails[i]));
}

bool BloomFilter::filter(const std::string& email) {
    MultiHashes mh(this->size, email);
    for(std::size_t i=0; i<numHashes; i++)
        if(!this->bits[mh()]) return false;
    return true;
}






