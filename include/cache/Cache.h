#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include "cache/CacheLine.h"

class Cache {
private:
    int cacheSize;
    int blockSize;
    int associativity;

    int numSets;
    int time;

    std::vector<std::vector<CacheLine>> sets;

    int hits;
    int misses;

public:
    Cache(int cacheSize, int blockSize, int associativity);

    bool probe(int address);
    void fill(int address);

    void printStats(const std::string& name);
};

#endif
