# Memory Management Simulator

A command-line simulator that models core operating system memory management concepts including:
- Dynamic memory allocation
- Buddy allocation
- Multilevel CPU cache (L1/L2)
- Set-associative cache with LRU replacement
- Virtual memory with paging and FIFO page replacement

## Features
- First Fit, Best Fit, Worst Fit allocation
- External and internal fragmentation metrics
- Buddy allocator with XOR-based merging
- L1/L2 cache simulation with associativity
- Cache hit/miss statistics
- Virtual memory paging and page faults

## Design Document/Test Artifacts

https://www.notion.so/MEMORY-MANAGEMENT-SIMULATOR-2e20c9cf76f28029a328f6be5af196c9?source=copy_link
- The design document was authored in Notion for structured writing and exported to PDF for formal submission; the Notion link is provided for reference.


## Build Instructions
```bash
make clean
make
