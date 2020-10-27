/**
 * CSF Fall 2020
 * Cache counter implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#include "cacheblock.h"

namespace CacheSimulator {
    void CacheBlock::setDirty() {
        _dirty = true;
    }

    void CacheBlock::clearDirty() {
        _dirty = false;
    }

    void CacheBlock::countTime() {
        _time++;
    }

    void CacheBlock::resetTime() {
        _time = 0;
    }

    void CacheBlock::updateTag(std::string tag) {
        _tag = tag;
    }

    void CacheBlock::setEmpty() {
        _isEmpty = true;
    }
}