/**
 * CSF Fall 2020
 * Cache counter implementation
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

namespace CacheSimulator {
    void CacheSet::addBlock(CacheBlock block) {
        _blocks.push_back(block);
    }

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

    CacheBlock *CacheSet::getBlockEvict() {
        for (std::vector<CacheBlock>::iterator it = _blocks.begin(); it != _blocks.end(); ++it) {
            if ((unsigned int) it->getTime() + 1 == _blocks.size())
                return &(*it);
        }
        return new CacheBlock(0, true);
    }

    void CacheSet::countTimerAll() {
        for (std::vector<CacheBlock>::iterator it = _blocks.begin(); it != _blocks.end(); ++it)
            it->countTime();
    }

    void CacheSet::countTimer(int time) {
        for (std::vector<CacheBlock>::iterator it = _blocks.begin(); it != _blocks.end(); ++it) {
            if (it->getTime() < time)
                it->countTime();
            else if (it->getTime() == time)
                it->resetTime();
        }
    }

    CacheBlock *CacheSet::findBlockFromTime(int time) {
        for (std::vector<CacheBlock>::iterator it = _blocks.begin(); it != _blocks.end(); ++it) {
            if (it->getTime() == time)
                return &(*it);
        }
        return new CacheBlock(0, true);
    }

    void CacheSet::setFirstBlock(std::string tag) {
        _firstBlockTag = tag;
    }

    void CacheSet::addFirstBlock() {
        CacheBlock *block = new CacheBlock(_firstBlockTag);
        if (_firstBlockDirty)
            block->setDirty();
        _blocks.push_back(*block);
        delete block;
    }

    void CacheSet::setFirstDirty() {
        _firstBlockDirty = true;
    }

}