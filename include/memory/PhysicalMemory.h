#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <vector>
#include "MemoryBlock.h"

class PhysicalMemory {
private:
    size_t totalSize;
    std::vector<MemoryBlock> blocks;

public:
    explicit PhysicalMemory(size_t size);
    // Allocate memory of given size
    // Returns start address, or -1 if allocation fails
    int allocate(size_t size);

    // Free memory at given start address
    void freeBlock(size_t startAddress);
    void dumpMemory() const;
};

#endif
