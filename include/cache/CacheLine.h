#ifndef CACHE_LINE_H
#define CACHE_LINE_H

struct CacheLine {
    bool valid;
    int tag;
    int timestamp;   // used later for FIFO/LRU

    CacheLine() : valid(false), tag(-1), timestamp(0) {}
};

#endif
