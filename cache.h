/**
 * CSF Fall 2020
 * Cache header file
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

/* 
 * Cache class whose instances are the cache.
 */
namespace CacheSimulator {
    class Cache {
    public:
        Cache() {};

        /* 
        * Constructor of the cache 
        *
        * Parameters:
        *  numSets - int number of sets in cache
        *  numBlocks - int number of blocks in cache
        *  blockSize - int number of sets in cache
        *  cacheStore - int number of cache stores
        *  memoryWrite - int number of memory writes
        *  evict - int number of evicts
        */
        Cache(int numSets, int numBlocks, int blockSize, int cacheStore, int memoryWrite, int evict) {
            _numSets = numSets;
            _numBlocks = numBlocks;
            _blockSize = blockSize;
            _cacheStore = cacheStore;
            _memoryWrite = memoryWrite;
            _evict = evict;
        }
        
        /* 
        * Add set to cache
        *
        * Parameters:
        *  index - string to indicate index of set added
        * 
        * Returns:
        *  new CacheSet that was created 
        */
        CacheSet *addSet(std::string index);

        /* 
        * Find set in cache given index or return new one
        *
        * Parameters:
        *  index - string to indicate index of set added
        * 
        * Returns:
        *  CacheSet referred to by index given or new CacheSet
        */
        CacheSet *findSet(std::string index);

        int getNumSets() {
            return _num_sets_stored;
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
        int read(std::string index, std::string tag, std::string &firstTag);
        
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
        int write(std::string index, std::string tag, std::string &firstTag, bool &dirty);

        /* 
        * Function to display the field information of the cache
        */
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

        /* 
        * Do operations necessary when reading data from cache
        *
        * Parameters:
        *  block - pointer to CacheBlock instance to read from
        *  set - pointer to CacheSet instance to read from
        *  tag - string to indicate tag of address
        */
        void readFromCache(CacheBlock *block, CacheSet *set, std::string tag);

        // write functions

        /* 
        * Helper method for write when block is originally nonempty
        *
        * Parameters:
        *  set - pointer to CacheSet instance to read from
        *  block - pointer to CacheBlock instance to read from
        *  tag - string to indicate tag of address
        */
        void writeToCache(CacheSet *set, CacheBlock *block, std::string tag);
        
        /* 
        * Helper method for write when set is originally nonempty
        *
        * Parameters:
        *  set - pointer to CacheSet instance to read from
        *  block - pointer to CacheBlock instance to read from
        *  tag - string to indicate tag of address
        */
        void writeLogic(CacheSet *set, CacheBlock *block, std::string tag);
        
        /* 
        * Function to update indicated block
        *
        * Parameters:
        *  set - pointer to CacheSet instance to read from
        *  block - pointer to CacheBlock instance to read from
        *  tag - string to indicate tag of address
        */
        void updateBlock(CacheSet *set, CacheBlock *block, std::string tag);
        
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
        void writeCache(CacheSet *set, CacheBlock *block, std::string &firstTag, bool &firstDirty, std::string index, std::string tag);

        // set dictionary
        std::unordered_map <std::string, CacheSet> sets;
    };
}

#endif
