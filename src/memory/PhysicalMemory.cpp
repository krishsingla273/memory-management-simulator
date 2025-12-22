#include "memory/PhysicalMemory.h"
#include <iostream>

// Constructor: runs when we create a PhysicalMemory object
PhysicalMemory::PhysicalMemory(size_t size) {
    // Store total memory size
    totalSize = size;

    // At the start, all memory is free
    // One block starting at address 0, of full size
    MemoryBlock initialBlock(0, size, true);

    // Add this block to the list of blocks
    blocks.push_back(initialBlock);
}

// Prints the current memory layout
void PhysicalMemory::dumpMemory() const {
    std::cout << "Memory Layout:\n";

    // Go through each memory block
    for (const MemoryBlock& block : blocks) {

        std::cout << "[Start: " << block.start
                  << ", Size: " << block.size
                  << ", ";

        // Check whether block is free or allocated
        if (block.isFree) {
            std::cout << "Free";
        } else {
            std::cout << "Allocated";
        }

        std::cout << "]\n";
    }
}
// Allocate memory
int PhysicalMemory::allocate(size_t size) {

    // Loop through all memory blocks
    for (size_t i = 0; i < blocks.size(); i++) {

        // Check if block is free and large enough
        if (blocks[i].isFree && blocks[i].size >= size) {

            size_t startAddress = blocks[i].start;
            size_t remainingSize = blocks[i].size - size;

            // Mark current block as allocated
            blocks[i].isFree = false;
            blocks[i].size = size;

            // If memory remains, create a new free block
            if (remainingSize > 0) {
                MemoryBlock newBlock(
                    startAddress + size,
                    remainingSize,
                    true
                );

                blocks.insert(blocks.begin() + i + 1, newBlock);
            }

            // Return start address of allocated memory
            return (int)startAddress;
        }
    }

    // No suitable free block found
    return -1;
}


// Free allocated memory
void PhysicalMemory::freeBlock(size_t startAddress) {

    // Find the block with this start address
    for (size_t i = 0; i < blocks.size(); i++) {

        if (blocks[i].start == startAddress) {

            // Mark block as free
            blocks[i].isFree = true;

            // Merge with next block if free
            if (i + 1 < blocks.size() && blocks[i + 1].isFree) {
                blocks[i].size += blocks[i + 1].size;
                blocks.erase(blocks.begin() + i + 1);
            }

            // Merge with previous block if free
            if (i > 0 && blocks[i - 1].isFree) {
                blocks[i - 1].size += blocks[i].size;
                blocks.erase(blocks.begin() + i);
            }

            return;
        }
    }
}
