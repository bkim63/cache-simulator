/**
 * CSF Fall 2020
 * Cache counter implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <string>
#include "cacheset.h"

namespace CacheSimulator {
    class Cache {
    public:
        Cache() {};

        Cache(int numSets, int numBlocks, int blockSize, int cacheStore, int memoryWrite, int evict) {
            _numSets = numSets;
            _numBlocks = numBlocks;
            _blockSize = blockSize;
            _cacheStore = cacheStore;
            _memoryWrite = memoryWrite;
            _evict = evict;
        }

        CacheSet *addSet(std::string index);
        CacheSet *findSet(std::string index);

        int getNumSets() {
            return _num_sets_stored;
        }

        int read(std::string index, std::string tag, std::string &firstTag);
        int write(std::string index, std::string tag, std::string &firstTag, bool &dirty);

        void displaySimulator();

    private:
        // instance variables initialized as 0
        int _num_sets_stored = 0;
        int _numSets = 0;
        int _numBlocks = 0;
        int _blockSize = 0;
        int _cacheStore = 0;
        int _memoryWrite = 0;
        int _evict = 0;
        int _loadHits = 0;
        int _loadMisses = 0;
        int _storeHits = 0;
        int _storeMisses = 0;
        int _numCycles = 0;

        // read functions
        void readFromCache(CacheBlock *block, CacheSet *set, std::string tag);

        // write functions
        void writeToCache(CacheSet *set, CacheBlock *block, std::string tag);
        void writeLogic(CacheSet *set, CacheBlock *block, std::string tag);
        void updateBlock(CacheSet *set, CacheBlock *block, std::string tag);
        void writeCache(CacheSet *set, CacheBlock *block, std::string &firstTag, bool &firstDirty, std::string index, std::string tag);

        // set dictionary
        std::unordered_map <std::string, CacheSet> sets;
    };
}

#endif
