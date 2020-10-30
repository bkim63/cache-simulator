/**
 * CSF Fall 2020
 * CacheSet implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#include <vector>
#include <iostream>
#include <string>
#include "cacheset.h"

/* 
 * CacheSet class whose instance is a set in the cache.
 */
namespace CacheSimulator {
    /* 
     * Function to add block into blocks vector
     * 
     * Parameters:
     *  block - CacheBlock to add
     */
    void CacheSet::addBlock(CacheBlock block) {
        _blocks.push_back(block);
    }

    /* 
     * Function to find block in cache set
     * 
     * Parameters:
     *  tag - string that represents tag
     * 
     * Returns:
     *  CacheBlock indicated by tag
     */
    CacheBlock *CacheSet::findBlock(std::string tag) {
        int tagInteger = stoi(tag, 0, 2);
        int blockTag;

        for (std::vector<CacheBlock>::iterator it = _blocks.begin(); it != _blocks.end(); ++it) {
            blockTag = stoi(it->getTag(), 0, 2);
            if (blockTag == tagInteger)
                return &(*it);
        }
        return new CacheBlock(0, true);
    }

    /* 
     * Function to get block to evict
     * 
     * Returns:
     *  CacheBlock block to evict
     */
    CacheBlock *CacheSet::getBlockEvict() {
        for (std::vector<CacheBlock>::iterator it = _blocks.begin(); it != _blocks.end(); ++it) {
            if ((unsigned int) it->getTime() + 1 == _blocks.size())
                return &(*it);
        }
        return new CacheBlock(0, true);
    }

    /* 
     * Function to caalculate the time
     */
    void CacheSet::countTimerAll() {
        for (std::vector<CacheBlock>::iterator it = _blocks.begin(); it != _blocks.end(); ++it)
            it->countTime();
    }

    /* 
     * Function to calculate/reset time depending on the time parameter
     * 
     * Parameters:
     *  time - int that is the time to consider
     */
    void CacheSet::countTimer(int time) {
        for (std::vector<CacheBlock>::iterator it = _blocks.begin(); it != _blocks.end(); ++it) {
            if (it->getTime() < time)
                it->countTime();
            else if (it->getTime() == time)
                it->resetTime();
        }
    }

    /* 
     * Function to find the block associated to time given
     * 
     * Parameters:
     *  time - int that is the time to consider
     * 
     * Returns:
     *  CacheBlock that is the block associated to the time provided
     */
    CacheBlock *CacheSet::findBlockFromTime(int time) {
        for (std::vector<CacheBlock>::iterator it = _blocks.begin(); it != _blocks.end(); ++it) {
            if (it->getTime() == time)
                return &(*it);
        }
        return new CacheBlock(0, true);
    }

    /* 
     * Setter for firstBlockTag field
     * 
     * Parameters:
     *  tag - string that is the tag to be set
     */
    void CacheSet::setFirstBlock(std::string tag) {
        _firstBlockTag = tag;
    }

    /* 
     * Function to add first block in cache set
     */
    void CacheSet::addFirstBlock() {
        CacheBlock *block = new CacheBlock(_firstBlockTag);
        if (_firstBlockDirty)
            block->setDirty();
        _blocks.push_back(*block);
        delete block;
    }

    /* 
     * Set cache set's first block to be dirty
     */
    void CacheSet::setFirstDirty() {
        _firstBlockDirty = true;
    }

}