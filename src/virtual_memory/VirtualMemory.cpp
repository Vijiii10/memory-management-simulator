#include <iostream>
#include "virtual_memory/VirtualMemory.h"

VirtualMemory::VirtualMemory(int vSize, int pSize, int pSizePg) {
    virtualSize = vSize;
    physicalSize = pSize;
    pageSize = pSizePg;

    numPages = virtualSize / pageSize;
    numFrames = physicalSize / pageSize;

    pageTable.resize(numPages);

    pageFaults = 0;
    pageHits = 0;
}

int VirtualMemory::access(int virtualAddress) {
    int pageNumber = virtualAddress / pageSize;
    int offset = virtualAddress % pageSize;

    if (pageNumber >= numPages) {
        std::cout << "Invalid virtual address\n";
        return -1;
    }

    // PAGE HIT
    if (pageTable[pageNumber].valid) {
        pageHits++;
        int frame = pageTable[pageNumber].frameNumber;
        return frame * pageSize + offset;
    }

    // PAGE FAULT
    pageFaults++;

    int frame;

    if ((int)fifoQueue.size() < numFrames) {
        frame = fifoQueue.size();
    } else {
        int victimPage = fifoQueue.front();
        fifoQueue.pop();

        frame = pageTable[victimPage].frameNumber;
        pageTable[victimPage].valid = false;
    }

    pageTable[pageNumber].valid = true;
    pageTable[pageNumber].frameNumber = frame;
    fifoQueue.push(pageNumber);

    return frame * pageSize + offset;
}

void VirtualMemory::stats() {
    int total = pageHits + pageFaults;
    double hitRate = total == 0 ? 0 : (double)pageHits / total;

    std::cout << "Page Hits: " << pageHits << "\n";
    std::cout << "Page Faults: " << pageFaults << "\n";
    std::cout << "Hit Rate: " << hitRate * 100 << "%\n";
}
