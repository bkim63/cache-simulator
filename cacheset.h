/**
 * CSF Fall 2020
 * CacheSet header file
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

/* 
 * CacheSet class whose instance is a set in the cache.
 */
namespace CacheSimulator {
    class CacheSet {
    private:
        std::vector <CacheBlock> _blocks;
        std::string _firstBlockTag = "";

        bool _firstBlockDirty = false;
        bool _isEmpty = false;

    public:
        /* 
        * Empty constructor for cache set
        */ 
        CacheSet() {};

        /* 
        * Constructor given isEmpty boolean parameter
        * 
        * Parameters:
        *  isEmpty - bool to set _isEmpty field to
        */
        CacheSet(bool isEmpty) {
            _isEmpty = isEmpty;

            _firstBlockTag = "";
            _firstBlockDirty = false;
        }

        /* 
        * Function to return number of blocks stored in set
        *
        * Returns:
        *  int number of blocks stored in set
        */
        int getNumBlocksStored() {
            return _blocks.size();
        }

        /* 
        * Function to indicate if set is empty
        * 
        * Returns:
        *  boolean to show if set is empty
        */
        bool isEmpty() {
            return _isEmpty;
        }

        /* 
        * Function to add block into blocks vector
        * 
        * Parameters:
        *  block - CacheBlock to add
        */
        void addBlock(CacheBlock cb);

        /* 
        * Function to find block in cache set
        * 
        * Parameters:
        *  tag - string that represents tag
        * 
        * Returns:
        *  CacheBlock indicated by tag
        */
        CacheBlock *findBlock(std::string tag);

        /* 
        * Function to get block to evict
        * 
        * Returns:
        *  CacheBlock block to evict
        */
        CacheBlock *getBlockEvict();

        /* 
        * Function to caalculate the time
        */
        void countTimerAll();

        /* 
        * Function to calculate/reset time depending on the time parameter
        * 
        * Parameters:
        *  time - int that is the time to consider
        */
        void countTimer(int time);

        /* 
        * Function to find the block associated to time given
        * 
        * Parameters:
        *  time - int that is the time to consider
        * 
        * Returns:
        *  CacheBlock that is the block associated to the time provided
        */
        CacheBlock *findBlockFromTime(int time);

        /* 
        * Setter for firstBlockTag field
        * 
        * Parameters:
        *  tag - string that is the tag to be set
        */
        void setFirstBlock(std::string tag);

        /* 
        * Function to add first block in cache set
        */
        void addFirstBlock();

        /* 
        * Set cache set's first block to be dirty
        */
        void setFirstDirty();
    };
}

#endif
