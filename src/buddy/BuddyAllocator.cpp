#include <iostream>
#include <cmath>
#include "buddy/BuddyAllocator.h"

int BuddyAllocator::nextPowerOfTwo(int size) {
    int power = 1;
    while (power < size)
        power <<= 1;
    return power;
}

BuddyAllocator::BuddyAllocator(int total, int minBlock) {
    totalSize = total;
    minBlockSize = minBlock;

    freeLists[totalSize].push_back(0); // entire memory free
}

int BuddyAllocator::allocate(int size) {
    int reqSize = nextPowerOfTwo(size);

    if (reqSize < minBlockSize)
        reqSize = minBlockSize;

    int currentSize = reqSize;

    // Find the smallest available block >= reqSize
    while (currentSize <= totalSize) {
        if (!freeLists[currentSize].empty()) {
            int address = freeLists[currentSize].back();
            freeLists[currentSize].pop_back();

            // Split until we reach requested size
            while (currentSize > reqSize) {
                currentSize /= 2;
                freeLists[currentSize].push_back(address + currentSize);
            }

            std::cout << "Buddy allocated at address "
                      << address << " size " << reqSize << "\n";

            return address;
        }
        currentSize *= 2;
    }

    std::cout << "Allocation failed\n";
    return -1;
}


void BuddyAllocator::freeBlock(int address, int size) {
    int blockSize = nextPowerOfTwo(size);

    while (blockSize < totalSize) {
        int buddy = address ^ blockSize;

        auto &list = freeLists[blockSize];
        auto it = std::find(list.begin(), list.end(), buddy);

        if (it == list.end())
            break;

        list.erase(it);
        address = std::min(address, buddy);
        blockSize *= 2;
    }

    freeLists[blockSize].push_back(address);
    std::cout << "Buddy block freed and merged\n";
}

void BuddyAllocator::dump() {
    for (auto &entry : freeLists) {
        std::cout << "Block size " << entry.first << ": ";
        for (int addr : entry.second)
            std::cout << addr << " ";
        std::cout << "\n";
    }
}
