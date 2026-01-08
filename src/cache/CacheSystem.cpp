#include <iostream>
#include "cache/CacheSystem.h"

CacheSystem::CacheSystem(int l1Size, int l2Size, int blockSize, int assoc) {
    L1 = new Cache(l1Size, blockSize, assoc);
    L2 = new Cache(l2Size, blockSize, assoc);
}

CacheSystem::~CacheSystem() {
    delete L1;
    delete L2;
}

void CacheSystem::access(int address) {

    if (L1->probe(address)) {
        std::cout << "L1 HIT\n";
        return;
    }

    if (L2->probe(address)) {
        std::cout << "L1 MISS → L2 HIT\n";

        L1->fill(address);
        return;
    }

    std::cout << "L1 MISS → L2 MISS → Memory Access\n";

    L2->fill(address);
    L1->fill(address);
}



void CacheSystem::stats() {
    L1->printStats("L1");
    L2->printStats("L2");
}
