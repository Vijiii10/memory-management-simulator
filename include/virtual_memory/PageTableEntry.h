#ifndef PAGE_TABLE_ENTRY_H
#define PAGE_TABLE_ENTRY_H

struct PageTableEntry {
    bool valid;
    int frameNumber;

    PageTableEntry() : valid(false), frameNumber(-1) {}
};

#endif
