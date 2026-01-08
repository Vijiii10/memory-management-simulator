#ifndef BLOCK_H
#define BLOCK_H

struct Block {
    int start;          // start address
    int size;           // allocated block size
    int requestedSize;  // requested by user
    bool free;
    int id;
};

#endif
