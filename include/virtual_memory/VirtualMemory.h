#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <vector>
#include <queue>
#include "virtual_memory/PageTableEntry.h"

class VirtualMemory {
private:
    int virtualSize;
    int physicalSize;
    int pageSize;

    int numPages;
    int numFrames;

    std::vector<PageTableEntry> pageTable;
    std::queue<int> fifoQueue;

    int pageFaults;
    int pageHits;

public:
    VirtualMemory(int virtualSize, int physicalSize, int pageSize);

    int access(int virtualAddress);
    void stats();
};

#endif
