#ifndef BLOOMFILTER_OMP_BLOOMFILTERPAR_H
#define BLOOMFILTER_OMP_BLOOMFILTERPAR_H


#include "BloomFilter.h"
#include "MultiHashes.h"


class BloomFilterPar : public BloomFilter{
public:
    BloomFilterPar(size_t size, std::string *emails, size_t nEmails);

private:
    void setup(std::size_t numHashes, std::string emails[], std::size_t nEmails) override;

};


#endif //BLOOMFILTER_OMP_BLOOMFILTERPAR_H
