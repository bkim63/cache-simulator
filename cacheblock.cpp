/**
 * CSF Fall 2020
 * Cache block implementation file
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#include "cacheblock.h"
#include "cacheconfig.h"
#include <vector>

namespace CacheSimulator {
    uint32_t CacheBlock::getAddress() const {
        uint32_t offset_bits = _cache_config.getNumBlockOffsetBits();
        uint32_t index_bits = _cache_config.getNumIndexBits();
        //uint32_t tag_bits = _cache_config.getNumTagBits();
        uint32_t ret = getTag();

        ret = ((ret << index_bits) + _index);
        return (ret << offset_bits);
    }

    uint32_t CacheBlock::getTag() const {
        ++_touches;
        return _tag;
    }

    void CacheBlock::setTag(uint32_t tag) {
        _tag = tag;
    }

    bool CacheBlock::isValid() const {
        return _valid;
    }

    void CacheBlock::markAsValid() {
        _valid = true;
    }

    void CacheBlock::markAsDirty() {
        _dirty = true;
    }

    bool CacheBlock::isDirty() const {
        return _dirty;
    }

    uint32_t CacheBlock::getLastUsedTime() const {
        return _last_used_time;
    }

    void CacheBlock::markAsClean() {
        _dirty = false;
    }

    void CacheBlock::setLastUsedTime(uint32_t time) {
        _last_used_time = time;
    }

    void CacheBlock::writeDataToMemory(Memory *memory) const {
        memory->writeBlock(getAddress(), _data);
    }

    void CacheBlock::readDataFromMemory(Memory *memory) {
        _data = memory->readBlock(getAddress(), _data.size());
    }

    uint32_t CacheBlock::readWordAtOffset(uint32_t block_offset) const {
        assert(block_offset < _data.size());
        ++_reads;
        return _data[block_offset];
    }

    void CacheBlock::writeWordAtOffset(uint32_t data, uint32_t block_offset) {
        assert(block_offset < _data.size());
        ++_writes;
        _data[block_offset] = data;
    }

    uint32_t CacheBlock::getStoredTime() const {
        return _stored_time;
    }

    void CacheBlock::setStoredTime(uint32_t storedTime) {
        _stored_time = storedTime;
    }
}
