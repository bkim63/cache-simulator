/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#include <unordered_map>
#include <map>
#include <string>
#include "cache.h"

/* 
 * Cache class whose instances are the cache.
 */
namespace CacheSimulator {
    /* 
     * Add set to cache
     *
     * Parameters:
     *  index - string to indicate index of set added
     * 
     * Returns:
     *  new CacheSet that was created 
     */
    CacheSet *Cache::addSet(std::string index) {
        CacheSet *set = new CacheSet();
        sets[index] = *set;
        _num_sets_stored++;

        return set;
    }

    /* 
     * Find set in cache given index or return new one
     *
     * Parameters:
     *  index - string to indicate index of set added
     * 
     * Returns:
     *  CacheSet referred to by index given or new CacheSet
     */
    CacheSet *Cache::findSet(std::string index) {
        std::unordered_map<std::string, CacheSet>::iterator it = sets.find(index);

        if (it != sets.end())
            return &sets[index];

        return new CacheSet(true);
    }

    /* 
     * Do operations necessary when reading data from cache
     *
     * Parameters:
     *  block - pointer to CacheBlock instance to read from
     *  set - pointer to CacheSet instance to read from
     *  tag - string to indicate tag of address
     */
    void Cache::readFromCache(CacheBlock *block, CacheSet *set, std::string tag) {
        if (block->isEmpty()) {
            delete block;

            _loadMisses++;
            _numCycles += 100 * _blockSize / 4 + 1;

            if (set->getNumBlocksStored() == _numBlocks) {
                block = set->findBlockFromTime(_numBlocks - 1);
                if (_memoryWrite == 1 && block->getDirty()) {
                    _numCycles += 100 * _blockSize / 4;
                    block->clearDirty();
                }
                set->countTimerAll();
                block->resetTime();
                block->updateTag(tag);
            } else {
                set->countTimerAll();
                block = new CacheBlock(tag);
                set->addBlock(*block);
                delete block;
            }
        } else {
            _loadHits++;
            _numCycles++;
            if (_evict == 0)
                set->countTimer(block->getTime());
        }
    }

    /* 
     * Function to read from cache
     *
     * Parameters:
     *  index - string of index to find set
     *  tag - string to indicate tag of address
     *  firstTag - string reference of first tag
     * 
     * Returns:
     *  int to indicate whether we can read from set
     */
    int Cache::read(std::string index, std::string tag, std::string &firstTag) {
        CacheSet *set = findSet(index);
        CacheBlock *block;

        if (set->isEmpty()) {
            delete set;
            if (getNumSets() == _numSets) {
                std::cerr << "Index is invalid" << std::endl;
                return -1;
            }
            _loadMisses++;

            set = addSet(index);
            block = new CacheBlock(tag);
            set->addBlock(*block);
            firstTag = tag;

            _numCycles += 100 * _blockSize / 4 + 1;

            delete set;
            delete block;
        } else {
            block = set->findBlock(tag);
            readFromCache(block, set, tag);
        }
        set = NULL;
        block = NULL;

        return 0;
    }

    /* 
     * Function to write to cache
     *
     * Parameters:
     *  index - string of index to find set
     *  tag - string to indicate tag of address
     *  firstTag - string reference of first tag
     *  firstDirty - boolean reference to indicate first dirty bit
     * 
     * Returns:
     *  int to indicate whether we can write to set
     */
    int Cache::write(std::string index, std::string tag, std::string &firstTag, bool &firstDirty) {
        CacheSet *set = findSet(index);
        CacheBlock *block = nullptr;

        if (set->isEmpty()) {
            delete set;
            _storeMisses++;

            if (getNumSets() == _numSets) {
                std::cerr << "Invalid index" << std::endl;
                return -1;
            }

            writeCache(set, block, firstTag, firstDirty, index, tag);

        } else {
            writeLogic(set, block, tag);
        }
        set = nullptr;
        block = nullptr;

        return 0;
    }

    /* 
     * Do operations necessary when writing data to cache
     *
     * Parameters:
     *  set - pointer to CacheSet instance to read from
     *  block - pointer to CacheBlock instance to read from
     *  firstTag - string reference of first tag
     *  firstDirty - boolean reference to indicate first dirty bit
     *  index - string of index to find set
     *  tag - string to indicate tag of address
     */
    void Cache::writeCache(CacheSet *set, CacheBlock *block, std::string &firstTag, bool &firstDirty, std::string index, std::string tag) {
        if (_cacheStore == 0) {
            set = addSet(index);
            block = new CacheBlock(tag);
            set->addBlock(*block);

            firstTag = tag;
            firstDirty = true;

            delete set;
            delete block;

            _numCycles += 100 * _blockSize / 4;

            if (_memoryWrite == 0)
                _numCycles += 101;
            else
                _numCycles++;
        } else
            _numCycles += 100;
    }

    /* 
     * Helper method for write when set is originally nonempty
     *
     * Parameters:
     *  set - pointer to CacheSet instance to read from
     *  block - pointer to CacheBlock instance to read from
     *  tag - string to indicate tag of address
     */
    void Cache::writeLogic(CacheSet *set, CacheBlock *block, std::string tag) {
        block = set->findBlock(tag);

        if (block->isEmpty()) {
            writeToCache(set, block, tag);
        } else {
            _storeHits++;

            if (_memoryWrite == 1)
                block->setDirty();
            if (_cacheStore == 1)
                _numCycles += 100;
            else if (_memoryWrite == 0)
                _numCycles += 101;
            else
                _numCycles++;

            if (_evict == 0)
                set->countTimer(block->getTime());
        }
    }

    /* 
     * Function to update indicated block
     *
     * Parameters:
     *  set - pointer to CacheSet instance to read from
     *  block - pointer to CacheBlock instance to read from
     *  tag - string to indicate tag of address
     */
    void Cache::updateBlock(CacheSet *set, CacheBlock *block, std::string tag) {
        if (_numBlocks == set->getNumBlocksStored()) {
            block = set->findBlockFromTime(_numBlocks - 1);

            if (_memoryWrite == 1 && block->getDirty())
                _numCycles += 100 * _blockSize / 4;

            set->countTimerAll();
            block->resetTime();
            block->updateTag(tag);
        } else {
            set->countTimerAll();
            block = new CacheBlock(tag);
            set->addBlock(*block);

            if (_memoryWrite == 1)
                block->setDirty();

            delete block;
        }
    }

    /* 
     * Helper method for write when block is originally nonempty
     *
     * Parameters:
     *  set - pointer to CacheSet instance to read from
     *  block - pointer to CacheBlock instance to read from
     *  tag - string to indicate tag of address
     */
    void Cache::writeToCache(CacheSet *set, CacheBlock *block, std::string tag) {
        delete block;
        _storeMisses++;

        if (_cacheStore == 0) {
            updateBlock(set, block, tag);

            if (_cacheStore == 0) {
                _numCycles += 100 * _blockSize / 4;

                if (_memoryWrite == 0)
                    _numCycles += 101;
                else
                    _numCycles++;
            }
        } else
            _numCycles += 100;
    }

    /* 
     * Function to display the field information of the cache
     */
    void Cache::displaySimulator() {
        std::cout << "Total loads: " << (_loadHits + _loadMisses) << std::endl;
        std::cout << "Total stores: " << (_storeHits + _storeMisses) << std::endl;
        std::cout << "Load hits: " << _loadHits << std::endl;
        std::cout << "Load misses: " << _loadMisses << std::endl;
        std::cout << "Store hits: " << _storeHits << std::endl;
        std::cout << "Store misses: " << _storeMisses << std::endl;
        std::cout << "Total cycles: " << _numCycles << std::endl;
    }

}