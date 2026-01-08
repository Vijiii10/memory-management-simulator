#include <iostream>
#include <climits>
#include "cache/Cache.h"

Cache::Cache(int cSize, int bSize, int assoc) {
    cacheSize = cSize;
    blockSize = bSize;
    associativity = assoc;

    int numLines = cacheSize / blockSize;
    numSets = numLines / associativity;

    sets.resize(numSets, std::vector<CacheLine>(associativity));

    hits = 0;
    misses = 0;
    time = 0;
}

bool Cache::probe(int address) {
    time++;

    int blockNumber = address / blockSize;
    int setIndex = blockNumber % numSets;
    int tag = blockNumber / numSets;

    auto &set = sets[setIndex];

    for (auto &line : set) {
        if (line.valid && line.tag == tag) {
            hits++;
            line.timestamp = time;   // LRU update
            return true;
        }
    }

    misses++;
    return false;
}

void Cache::fill(int address) {
    time++;

    int blockNumber = address / blockSize;
    int setIndex = blockNumber % numSets;
    int tag = blockNumber / numSets;

    auto &set = sets[setIndex];

    int lruIndex = 0;
    int oldest = INT_MAX;

    for (int i = 0; i < associativity; i++) {
        if (!set[i].valid) {
            lruIndex = i;
            break;
        }
        if (set[i].timestamp < oldest) {
            oldest = set[i].timestamp;
            lruIndex = i;
        }
    }

    set[lruIndex].valid = true;
    set[lruIndex].tag = tag;
    set[lruIndex].timestamp = time;
}


void Cache::printStats(const std::string& name) {
    int total = hits + misses;
    double hitRate = total == 0 ? 0 : (double)hits / total;

    std::cout << name << " Cache Stats:\n";
    std::cout << "Hits: " << hits << "\n";
    std::cout << "Misses: " << misses << "\n";
    std::cout << "Hit Rate: " << hitRate * 100 << "%\n";
}
