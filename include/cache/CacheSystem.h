#ifndef CACHE_SYSTEM_H
#define CACHE_SYSTEM_H

#include "cache/Cache.h"

class CacheSystem {
private:
    Cache* L1;
    Cache* L2;

public:
    CacheSystem(int l1Size, int l2Size, int blockSize, int assoc);
    ~CacheSystem();

    void access(int address);
    void stats();
};

#endif
