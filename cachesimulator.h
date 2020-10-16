/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 * 2. Rebecca Shao
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

using std::uint32_t;

namespace CacheSimulator {
    class CacheSimulator {
    public:
        CacheSimulator(Cache* cache, Memory* memory)
                : _cache(cache), _memory(memory) {};

        uint32_t read(uint32_t address) const;
        void write(uint32_t address, uint32_t word) const;

        uint32_t getHits() const;

        void display();

    private:
        Cache* _cache;
        Memory* _memory;

        mutable Counter _use_clock;
        mutable Counter _hits;

        CacheBlock* findBlock(uint32_t address) const;
        CacheBlock* bringBlockIntoCache(uint32_t address) const;
    };
}

#endif
