#include <iostream>
#include <string>
#include "memory/PhysicalMemory.h"
#include "cache/SetAssociativeCache.h"
#include "vmm/VirtualMemoryManager.h"

using namespace std;

/* ---------------- STAGE 1–4 ---------------- */
void demoAllocator() {
    cout << "\n==============================\n";
    cout << "STAGE 1:4 : MEMORY ALLOCATION\n";
    cout << "==============================\n";

    int totalMemory;
    cin >> totalMemory;

    string strategy;
    cin >> strategy;

    AllocationStrategy strat;
    if (strategy == "FIRST_FIT") strat = FIRST_FIT;
    else if (strategy == "BEST_FIT") strat = BEST_FIT;
    else strat = WORST_FIT;

    PhysicalMemory mem(totalMemory, strat);

    int ops;
    cin >> ops;

    for (int i = 0; i < ops; i++) {
        string command;
        cin >> command;

        if (command == "malloc") {
            int sz;
            cin >> sz;
            int addr = mem.allocate(sz);
            if (addr == -1)
                cout << "malloc(" << sz << ") -> FAILED\n";
            else
                cout << "malloc(" << sz << ") -> address " << addr << "\n";
        }
        else if (command == "free") {
            int addr;
            cin >> addr;
            mem.freeBlock(addr);
            cout << "free(" << addr << ")\n";
        }

        mem.dumpMemory();
        cout << "External Fragmentation: "
             << mem.getExternalFragmentation() << "\n";
        cout << "Memory Utilization: "
             << mem.getMemoryUtilization() << "\n\n";
    }
}

void demoCache() {
    cout << "\n==============================\n";
    cout << "STAGE 5: CACHE HIERARCHY\n";
    cout << "==============================\n";

    SetAssociativeCache* L1 = nullptr;

    int commands;
    cin >> commands;

    for (int i = 0; i < commands; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "INIT_CACHE") {
            int cacheSize, blockSize, assoc;
            cin >> cacheSize >> blockSize >> assoc;

            delete L1; // safe even if nullptr
            L1 = new SetAssociativeCache(cacheSize, blockSize, assoc);

            cout << "Cache Initialized\n";
            cout << "Cache Size: " << cacheSize << "\n";
            cout << "Block Size: " << blockSize << "\n";
            cout << "Associativity: " << assoc << "\n\n";
        }

        else if (cmd == "CACHE_ACCESS") {
            int addr;
            cin >> addr;

            if (L1->contains(addr)) {
                L1->recordHit();
                L1->touch(addr);
                cout << addr << " -> HIT\n";
            } else {
                L1->recordMiss();
                L1->touch(addr);
                cout << addr << " -> MISS\n";
            }
        }

        else if (cmd == "CACHE_STATS") {
            cout << "\nCache Statistics:\n";
            cout << "Hit Ratio: " << L1->getHitRatio() << "\n\n";
        }
    }

    delete L1;
}
/* ---------------- STAGE 6 ---------------- */
void demoVirtualMemory() {
    cout << "\n==============================\n";
    cout << "STAGE 6: VIRTUAL MEMORY\n";
    cout << "==============================\n";

    int pageSize, virtualPages, physicalFrames;
    cin >> pageSize >> virtualPages >> physicalFrames;

    VirtualMemoryManager vmm(pageSize, virtualPages, physicalFrames);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int va;
        cin >> va;
        int pa = vmm.translate(va);
        cout << "VA " << va << " -> PA " << pa << "\n";
    }

    cout << "\nPage Faults: " << vmm.getPageFaults() << "\n";
    cout << "Page Fault Rate: " << vmm.getPageFaultRate() << "\n";
}

int main() {
    demoAllocator();
    demoCache();
    demoVirtualMemory();
    return 0;
}
