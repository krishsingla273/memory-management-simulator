#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <list>

class LRUCache {
private:
    int capacity;
    std::list<int> cache;   // front = MRU, back = LRU

    int hits;
    int misses;

public:
    LRUCache(int capacity);

    //  Pure check (NO mutation, NO stats)
    bool contains(int blockNumber) const;

    //  Accounting only
    void recordHit();
    void recordMiss();

    //  Structural update (insert / promote)
    void touch(int blockNumber);

    // Inclusion support
    void remove(int blockNumber);

    // Metrics
    int getHits() const;
    int getMisses() const;
    double getHitRatio() const;

    void printCache(const char* name) const;
};

#endif
