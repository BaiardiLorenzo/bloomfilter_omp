#include "MultiHashes.h"

MultiHashes::MultiHashes(std::size_t size, const std::string &email):
size(size),rand(std::hash<std::string>{} (email)){
    assert(size > 0);
}

std::size_t MultiHashes::operator()(){
    return rand()%size;
}

