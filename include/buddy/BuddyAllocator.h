#ifndef BUDDY_ALLOCATOR_H
#define BUDDY_ALLOCATOR_H

#include <map>
#include <vector>

class BuddyAllocator {
private:
    int totalSize;
    int minBlockSize;

    // free lists indexed by block size
    std::map<int, std::vector<int>> freeLists;

    int nextPowerOfTwo(int size);

public:
    BuddyAllocator(int totalSize, int minBlockSize);

    int allocate(int size);
    void freeBlock(int address, int size);

    void dump();
};

#endif
