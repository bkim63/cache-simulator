/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 * 2. Rebecca Shao
 */

#ifndef CACHE_BLOCK_H
#define CACHE_BLOCK_H

#include <cassert>
#include <cstdint>

#include "cache.h"
#include "memory.h"
#include "cacheconfig.h"

using std::uint32_t;
using std::vector;

namespace bkim63 {
    class CacheBlock {
    public:
        CacheBlock(uint32_t index, const CacheConfig &cache_config) : _index(index),
                                                                      _data(cache_config.getNumBytes()),
                                                                      _cache_config(cache_config) {}

        uint32_t getTag() const;
        void setTag(uint32_t tag);

        bool isValid() const;
        void markAsValid();

        bool isDirty() const;
        void markAsDirty();

        void markAsClean();

        uint32_t getLastUsedTime() const;
        void setLastUsedTime(uint32_t time);

        void writeDataToMemory(Memory *memory) const;
        void readDataFromMemory(Memory *memory);

        uint32_t readWordAtOffset(uint32_t block_offset) const;
        void writeWordAtOffset(uint32_t data, uint32_t block_offset);

        uint32_t getAddress() const;

    private:
        uint32_t _index;
        uint32_t _last_used_time;
        uint32_t _stored_time;
    public:
        uint32_t getStoredTime() const;

        void setStoredTime(uint32_t storedTime);

    private:
        uint32_t _tag;
        bool _valid;
        bool _dirty;

        vector<uint32_t> _data;

        const CacheConfig &_cache_config;

        // used for testing purposes
        mutable Counter _touches;
        mutable Counter _reads;
        mutable Counter _writes;
    };
}

#endif
