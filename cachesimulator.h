/**
 * CSF Fall 2020
 * Cache simulator function declarations
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#ifndef CACHE_SIMULATOR
#define CACHE_SIMULATOR

#include <cassert>
#include <cstdlib>

#include "cache.h"
#include "cacheblock.h"
#include "cacheconfig.h"
#include "counter.h"
#include "memory.h"
#include "utils.h"


namespace CacheSimulator {
    class CacheSimulator {
    public:
        CacheSimulator(Cache *cache, Memory *memory)
                : _cache(cache), _memory(memory) {};

        uint32_t read(uint32_t address) const;

        void write(uint32_t address, uint32_t word) const;

        uint32_t getHits() const;

        void display();

    private:
        Cache *_cache;
        Memory *_memory;

        mutable Counter _use_clock;
        mutable Counter _hits;

        CacheBlock *findBlock(uint32_t address) const;

        CacheBlock *bringBlockIntoCache(uint32_t address) const;

        void setBlock(uint32_t tag, CacheBlock *block) const;

        CacheBlock *getBlock(const CacheConfig &_cache_config, const std::vector<CacheBlock *> &cache_vec,
                             uint32_t time, size_t i) const;

        void setCacheBlock(uint32_t address, uint32_t word, CacheBlock *caching) const;
    };
}

#endif
