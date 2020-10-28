/**
 * CSF Fall 2020
 * CacheBlock implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#include "cacheblock.h"

namespace CacheSimulator {
    /* 
     * Make cache block dirty
     */
    void CacheBlock::setDirty() {
        _dirty = true;
    }

    /* 
     * Make cache block clean
     */
    void CacheBlock::clearDirty() {
        _dirty = false;
    }

    /* 
     * Increment time field of cache block
     */
    void CacheBlock::countTime() {
        _time++;
    }

    /* 
     * Reset time field to 0
     */
    void CacheBlock::resetTime() {
        _time = 0;
    }

    /* 
     * Setter for tag field
     * 
     * Parameters:
     *  tag - string to set _tag field to
     */
    void CacheBlock::updateTag(std::string tag) {
        _tag = tag;
    }

    /* 
     * Set cache block as empty
     */
    void CacheBlock::setEmpty() {
        _isEmpty = true;
    }
}