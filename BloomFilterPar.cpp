#include "BloomFilterPar.h"

void BloomFilterPar::setup(std::size_t numHashes, std::string emails[], std::size_t nEmails) {
    double start = omp_get_wtime();
#pragma omp parallel for default(none) shared(bits, emails) firstprivate(nEmails, numHashes)
    for(std::size_t i=0; i<nEmails; i++){
        MultiHashes mh(this->size, emails[i]);
        for(std::size_t j=0; j<numHashes; j++)
            this->bits[mh()] = true;
    }
    double time = omp_get_wtime() - start;
    printf("TIME SETUP PAR: %f\n", time);
}

BloomFilterPar::BloomFilterPar(std::size_t size, std::string emails[], std::size_t nEmails)
: BloomFilter(size, emails, nEmails) {

}
