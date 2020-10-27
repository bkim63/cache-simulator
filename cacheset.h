/**
 * CSF Fall 2020
 * CacheSet implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#ifndef CACHE_SET_H
#define CACHE_SET_H

#include <vector>
#include <iostream>
#include "cacheblock.h"

namespace CacheSimulator {
    class CacheSet {
    private:
        std::vector <CacheBlock> _blocks;
        std::string _firstBlockTag = "";

        bool _firstBlockDirty = false;
        bool _isEmpty = false;

    public:
        CacheSet() {};

        CacheSet(bool isEmpty) {
            _isEmpty = isEmpty;

            _firstBlockTag = "";
            _firstBlockDirty = false;
        }

        int getNumBlocksStored() {
            return _blocks.size();
        }

        bool isEmpty() {
            return _isEmpty;
        }

        void addBlock(CacheBlock cb);

        CacheBlock *findBlock(std::string tag);

        CacheBlock *getBlockEvict();

        void countTimerAll();

        void countTimer(int time);

        CacheBlock *findBlockFromTime(int time);

        void setFirstBlock(std::string tag);

        void addFirstBlock();

        void setFirstDirty();
    };
}

#endif
