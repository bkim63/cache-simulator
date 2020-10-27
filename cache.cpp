/**
 * CSF Fall 2020
 * Cache counter implementation
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

namespace CacheSimulator {
    CacheSet *Cache::addSet(std::string index) {
        CacheSet *set = new CacheSet();
        sets[index] = *set;
        _num_sets_stored++;

        return set;
    }

    CacheSet *Cache::findSet(std::string index) {
        std::unordered_map<std::string, CacheSet>::iterator it = sets.find(index);

        if (it != sets.end())
            return &sets[index];

        return new CacheSet(true);
    }

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