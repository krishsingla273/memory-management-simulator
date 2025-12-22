#include "cache/LRUCache.h"
#include <iostream>

LRUCache::LRUCache(int cap) {
    capacity = cap;
    hits = 0;
    misses = 0;
}

// Pure check
bool LRUCache::contains(int blockNumber) const {
    for (int b : cache) {
        if (b == blockNumber) return true;
    }
    return false;
}

//  Accounting
void LRUCache::recordHit() {
    hits++;
}

void LRUCache::recordMiss() {
    misses++;
}

//  Structural update
void LRUCache::touch(int blockNumber) {

    // If already present → promote to MRU
    for (auto it = cache.begin(); it != cache.end(); it++) {
        if (*it == blockNumber) {
            cache.erase(it);
            cache.push_front(blockNumber);
            return;
        }
    }

    // Evict LRU if full
    if ((int)cache.size() == capacity) {
        cache.pop_back();
    }

    cache.push_front(blockNumber);
}

// Inclusion support
void LRUCache::remove(int blockNumber) {
    for (auto it = cache.begin(); it != cache.end(); it++) {
        if (*it == blockNumber) {
            cache.erase(it);
            return;
        }
    }
}

// Metrics
int LRUCache::getHits() const {
    return hits;
}

int LRUCache::getMisses() const {
    return misses;
}

double LRUCache::getHitRatio() const {
    int total = hits + misses;
    if (total == 0) return 0.0;
    return (double)hits / total;
}

void LRUCache::printCache(const char* name) const {
    std::cout << name << " Cache (MRU → LRU): ";
    for (int b : cache) {
        std::cout << b << " ";
    }
    std::cout << "\n";
}
