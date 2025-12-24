#include <iostream>
#include "vmm/VirtualMemoryManager.h"
#include "cache/SetAssociativeCache.h"

int main() {

    // Stage 6: Virtual Memory
    VirtualMemoryManager vmm(
        100,   // page size
        10,    // virtual pages
        4      // physical frames
    );

    // Stage 5: Cache (physical-address based)
    SetAssociativeCache L1(4, 100, 2);  // 4 blocks, 2-way
    SetAssociativeCache L2(8, 100, 4);  // 8 blocks, 4-way

    int virtualAddresses[] = {
        10, 120, 250, 330,
        410, 120, 10, 250
    };

    for (int va : virtualAddresses) {

        //  Virtual → Physical
        int pa = vmm.translate(va);

        //  Cache hierarchy
        if (L1.contains(pa)) {
            L1.recordHit();
            L1.touch(pa);
        }
        else {
            L1.recordMiss();

            if (L2.contains(pa)) {
                L2.recordHit();
                L2.touch(pa);
                L1.touch(pa);   // promote
            }
            else {
                L2.recordMiss();
                L2.touch(pa);
                L1.touch(pa);
            }
        }

        std::cout << "VA " << va << " -> PA " << pa << "\n";
    }

    std::cout << "\n Metrics \n";
    std::cout << "Page Faults: " << vmm.getPageFaults() << "\n";
    std::cout << "Page Fault Rate: " << vmm.getPageFaultRate() << "\n";

    std::cout << "\nL1 Hit Ratio: " << L1.getHitRatio() << "\n";
    std::cout << "L2 Hit Ratio: " << L2.getHitRatio() << "\n";

    return 0;
}
