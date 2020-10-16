/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 * 2. Rebecca Shao
 */

#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <list>
#include <iterator>
#include <unordered_map>
#include <vector>

using namespace std;

namespace CacheSimulator {
    class CacheBlock;
    class CacheConfig;

    class Cache {
    public:
        vector<CacheBlock *> getBlocksInSet(uint32_t index) const;

        Cache(CacheConfig &cacheConfig);

        ~Cache();

        int getTotalLoads() const;

        void setTotalLoads(int totalLoads);

        int getTotalSets() const;

        void setTotalSets(int totalSets);

        int getLoadHits() const;

        void setLoadHits(int loadHits);

        int getLoadMisses() const;

        void setLoadMisses(int loadMisses);

        int getSetHits() const;

        void setSetHits(int setHits);

        int getSetMisses() const;

        void setSetMisses(int setMisses);

        int getTotalCycles() const;

        void setTotalCycles(int totalCycles);

        void setCacheConfig(CacheConfig &cacheConfig);

        CacheConfig &getCacheConfig() const;

        void setCacheConfig1(CacheConfig &cacheConfig);

    private:
        int _total_loads;
        int _total_sets;

        int _load_hits;
        int _load_misses;
        int _set_hits;
        int _set_misses;
        int _total_cycles;

        CacheConfig &_cache_config;
        vector<CacheBlock*> _blocks;

        void initBlocks();
    };
}

#endif
