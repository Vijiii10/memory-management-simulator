#include <iostream>
#include <sstream>

#include "MemoryManager.h"
#include "buddy/BuddyAllocator.h"
#include "cache/CacheSystem.h"
#include "virtual_memory/VirtualMemory.h"

int main() {
    MemoryManager mm;
    BuddyAllocator* buddy = nullptr;
    CacheSystem* cache = nullptr;
    VirtualMemory* vm = nullptr;
    bool useBuddy = false;

    std::string line;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        // ---------- NORMAL ALLOCATOR ----------
        if (cmd == "init") {
            int size; 
            ss >> size;
            mm.init(size);
            useBuddy = false;   // switch back to normal allocator
        }
        else if (cmd == "set") {
            std::string algo; 
            ss >> algo;
            if (algo == "first") mm.setStrategy(FIRST_FIT);
            else if (algo == "best") mm.setStrategy(BEST_FIT);
            else if (algo == "worst") mm.setStrategy(WORST_FIT);
        }

        // ---------- BUDDY ALLOCATOR ----------
        else if (cmd == "init_buddy") {
            int total, minBlock;
            ss >> total >> minBlock;

            if (buddy) delete buddy;
            buddy = new BuddyAllocator(total, minBlock);
            useBuddy = true;

            std::cout << "Buddy allocator initialized\n";
        }

        // ---------- MALLOC ----------
        else if (cmd == "malloc") {
            int size; 
            ss >> size;

            if (useBuddy && buddy) {
                buddy->allocate(size);
            } else {
                mm.allocate(size);
            }
        }

        // ---------- FREE ----------
        else if (cmd == "free") {
            if (useBuddy && buddy) {
                int address, size;
                ss >> address >> size;
                buddy->freeBlock(address, size);
            } else {
                int id;
                ss >> id;
                mm.freeBlock(id);
            }
        }

        // ---------- DUMP ----------
        else if (cmd == "dump") {
            if (!useBuddy)
                mm.dump();
        }
        else if (cmd == "dump_buddy") {
            if (useBuddy && buddy)
                buddy->dump();
        }

        // ---------- STATS ----------
        else if (cmd == "stats") {
            if (!useBuddy)
                mm.stats();
        }

        else if (cmd == "exit") {
            break;
        }

        // ---------- CACHE ----------
        else if (cmd == "init_cache") {
            int l1, l2, block, assoc;
            ss >> l1 >> l2 >> block >> assoc;

            if (cache) delete cache;
                cache = new CacheSystem(l1, l2, block, assoc);

            std::cout << "Cache system initialized\n";
        }
        else if (cmd == "access") {
            int addr;
            ss >> addr;

            if (cache)
                cache->access(addr);
        }
        else if (cmd == "cache_stats") {
            if (cache)
                cache->stats();
        }

        // ---------- VIRTUAL MEMORY ----------
        else if (cmd == "init_vm") {
            int v, p, page;
            ss >> v >> p >> page;

            if (vm) delete vm;
            vm = new VirtualMemory(v, p, page);

            std::cout << "Virtual memory initialized\n";
        }
        else if (cmd == "vm_access") {
            int addr;
            ss >> addr;

            if (vm) {
                int phys = vm->access(addr);
                if (phys != -1)
                    std::cout << "Physical address: " << phys << "\n";
            }
        }
        else if (cmd == "vm_stats") {
            if (vm)
                vm->stats();
        }


    }

    if (buddy) delete buddy;
    return 0;
}
