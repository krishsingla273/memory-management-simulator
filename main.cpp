#include <iostream>
#include "memory/PhysicalMemory.h"
#include "cache/LRUCache.h"

int main() {

    PhysicalMemory memory(1000, FIRST_FIT);

    LRUCache L1(3);  // small
    LRUCache L2(4);  // bigger

    int blockSize = 100;

    // Allocate memory (addresses)
    int addresses[] = {
        memory.allocate(100), // block 0
        memory.allocate(100), // block 1
        memory.allocate(100), // block 2
        memory.allocate(100), // block 3
        memory.allocate(100)  // block 4
    };

    int accessPattern[] = {0, 1, 2, 0, 3, 1, 4, 0};

    for (int idx : accessPattern) {

        int block = addresses[idx] / blockSize;

        // 🔹 L1 CHECK
        if (L1.contains(block)) {
            L1.recordHit();
            L1.touch(block);
            continue;
        }

        // L1 MISS
        L1.recordMiss();

        // 🔹 L2 CHECK
        if (L2.contains(block)) {
            L2.recordHit();
            L2.touch(block);

            // Promote to L1 (NO stats)
            L1.touch(block);
        }
        else {
            // L2 MISS
            L2.recordMiss();

            // Fetch from memory → insert into both
            L2.touch(block);
            L1.touch(block);
        }
    }

    std::cout << "\nFinal Cache State:\n";
    L1.printCache("L1");
    L2.printCache("L2");

    std::cout << "\nMetrics:\n";
    std::cout << "L1 Hits: " << L1.getHits()
              << ", Misses: " << L1.getMisses()
              << ", Hit Ratio: " << L1.getHitRatio() << "\n";

    std::cout << "L2 Hits: " << L2.getHits()
              << ", Misses: " << L2.getMisses()
              << ", Hit Ratio: " << L2.getHitRatio() << "\n";

    return 0;
}
