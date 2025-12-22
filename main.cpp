#include <iostream>
#include <string>
#include "memory/PhysicalMemory.h"

void testStrategy(AllocationStrategy strategy, const std::string& name) {

    std::cout << "\n========== " << name << " ==========\n";

    PhysicalMemory memory(1000, strategy);

    int a = memory.allocate(100);
    int b = memory.allocate(300);
    int c = memory.allocate(200);

    memory.freeBlock(b);

    memory.allocate(250);

    memory.dumpMemory();

    std::cout << "\nMetrics:\n";
    std::cout << "Total Free Memory: " << memory.getTotalFreeMemory() << "\n";
    std::cout << "Largest Free Block: " << memory.getLargestFreeBlock() << "\n";
    std::cout << "External Fragmentation: " 
              << memory.getExternalFragmentation() << "\n";
    std::cout << "Memory Utilization: " 
              << memory.getMemoryUtilization() << "\n";
    std::cout << "Allocation Success Rate: " 
              << memory.getAllocationSuccessRate() << "\n";
}

int main() {

    testStrategy(FIRST_FIT, "FIRST FIT");
    testStrategy(BEST_FIT, "BEST FIT");
    testStrategy(WORST_FIT, "WORST FIT");

    return 0;
}
