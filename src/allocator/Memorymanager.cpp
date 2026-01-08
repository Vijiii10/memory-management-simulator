#include <iostream>
#include <climits>
#include "MemoryManager.h"

MemoryManager::MemoryManager() {
    totalMemory = 0;
    nextId = 1;
    strategy = FIRST_FIT;
}

void MemoryManager::init(int size) {
    totalMemory = size;
    blocks.clear();
    blocks.push_back({0, size, 0, true, -1});
    std::cout << "Memory initialized: " << size << " bytes\n";
}

void MemoryManager::setStrategy(AllocStrategy s) {
    strategy = s;
}

int MemoryManager::allocate(int size) {
    auto chosen = blocks.end();

    if (strategy == FIRST_FIT) {
        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            if (it->free && it->size >= size) {
                chosen = it;
                break;
            }
        }
    }
    else if (strategy == BEST_FIT) {
        int bestSize = INT_MAX;
        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            if (it->free && it->size >= size && it->size < bestSize) {
                bestSize = it->size;
                chosen = it;
            }
        }
    }
    else if (strategy == WORST_FIT) {
        int worstSize = -1;
        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            if (it->free && it->size >= size && it->size > worstSize) {
                worstSize = it->size;
                chosen = it;
            }
        }
    }

    if (chosen == blocks.end()) {
        std::cout << "Allocation failed\n";
        return -1;
    }

    int id = nextId++;

    if (chosen->size > size) {
        Block newBlock = {
            chosen->start + size,
            chosen->size - size,
            0,
            true,
            -1
        };
        chosen->size = size;
        blocks.insert(std::next(chosen), newBlock);
    }

    chosen->free = false;
    chosen->id = id;
    chosen->requestedSize = size;

    std::cout << "Allocated block id=" << id
              << " at address=0x" << std::hex << chosen->start
              << std::dec << "\n";

    return id;
}

void MemoryManager::freeBlock(int id) {
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (!it->free && it->id == id) {
            it->free = true;
            it->id = -1;
            it->requestedSize = 0;

            // merge next
            auto next = std::next(it);
            if (next != blocks.end() && next->free) {
                it->size += next->size;
                blocks.erase(next);
            }

            // merge previous
            if (it != blocks.begin()) {
                auto prev = std::prev(it);
                if (prev->free) {
                    prev->size += it->size;
                    blocks.erase(it);
                }
            }

            std::cout << "Block " << id << " freed\n";
            return;
        }
    }
    std::cout << "Invalid block id\n";
}

void MemoryManager::dump() {
    for (auto &b : blocks) {
        std::cout << "[0x" << std::hex << b.start
                  << " - 0x" << (b.start + b.size - 1)
                  << "] " << std::dec;

        if (b.free)
            std::cout << "FREE\n";
        else
            std::cout << "USED (id=" << b.id << ")\n";
    }
}

void MemoryManager::stats() {
    int used = 0, free = 0, largestFree = 0;
    int internalFrag = 0;

    for (auto &b : blocks) {
        if (b.free) {
            free += b.size;
            largestFree = std::max(largestFree, b.size);
        } else {
            used += b.size;
            internalFrag += (b.size - b.requestedSize);
        }
    }

    double extFrag = free == 0 ? 0 :
        1.0 - ((double)largestFree / free);

    std::cout << "Total memory: " << totalMemory << "\n";
    std::cout << "Used memory: " << used << "\n";
    std::cout << "Free memory: " << free << "\n";
    std::cout << "External Fragmentation: "
              << extFrag * 100 << "%\n";
    std::cout << "Internal Fragmentation: "
            << internalFrag << " bytes\n";

}
