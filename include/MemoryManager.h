#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <list>
#include "Block.h"

enum AllocStrategy {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};

class MemoryManager {
private:
    int totalMemory;
    int nextId;
    AllocStrategy strategy;
    std::list<Block> blocks;

public:
    MemoryManager();

    void init(int size);
    void setStrategy(AllocStrategy s);

    int allocate(int size);
    void freeBlock(int id);

    void dump();
    void stats();
};

#endif
