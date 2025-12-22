#include <iostream>
#include "memory/PhysicalMemory.h"

int main() {

    PhysicalMemory memory(1024);

    int a = memory.allocate(200);
    int b = memory.allocate(300);

    memory.dumpMemory();

    std::cout << "\nFreeing first block...\n";
    memory.freeBlock(a);

    memory.dumpMemory();

    return 0;
}
