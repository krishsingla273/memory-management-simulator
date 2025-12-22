#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <vector>
#include "MemoryBlock.h"
enum AllocationStrategy {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};
class PhysicalMemory {
private:
    size_t totalSize;
    std::vector<MemoryBlock> blocks;
    AllocationStrategy strategy;
        // Metrics
    int totalRequests;
    int successfulRequests;


public:
    explicit PhysicalMemory(size_t size , AllocationStrategy strategy);
    // Allocate memory of given size
    // Returns start address, or -1 if allocation fails
    int allocate(size_t size);
    // Metrics
    size_t getTotalFreeMemory() const;
    size_t getLargestFreeBlock() const;
    double getExternalFragmentation() const;
    double getMemoryUtilization() const;
    double getAllocationSuccessRate() const;
    // Free memory at given start address
    void freeBlock(size_t startAddress);
    void dumpMemory() const;
};

#endif
