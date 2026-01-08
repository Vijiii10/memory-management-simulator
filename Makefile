CXX = g++
CXXFLAGS = -Wall -Iinclude

SRC = src/main.cpp \
      src/allocator/MemoryManager.cpp \
      src/buddy/BuddyAllocator.cpp \
      src/cache/Cache.cpp \
      src/cache/CacheSystem.cpp \
      src/virtual_memory/VirtualMemory.cpp

OUT = memsim

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
