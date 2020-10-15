/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * Steven (Bumjin) Kim
 * bkim63@jhu.edu
 */
#include "cachesimulator.h"

namespace bkim63 {
    CacheBlock *CacheSimulator::findBlock(uint32_t address) const {
        /**
         *
         * 1. Use `_cache->get_blocks_in_set` to get all the blocks that could
         *    possibly have `address` cached.
         * 2. Loop through all these blocks to see if any one of them actually has
         *    `address` cached (i.e. the block is valid and the tags match).
         * 3. If you find the block, increment `_hits` and return a pointer to the
         *    block. Otherwise, return NULL.
         */
        const CacheConfig &_cache_config = _cache->getCacheConfig();
        uint32_t index = extractIndex(address, _cache_config);

        vector<CacheBlock *> cache_vec = _cache->getBlocksInSet(index);
        uint32_t tag = extractTag(address, _cache_config);

        for (size_t i = 0; i < cache_vec.size(); i++) {
            if (cache_vec[i]->getTag() == tag && cache_vec[i]->isValid()) {
                _hits++;
                return cache_vec[i];
            }
        }

        return nullptr;
    }

    CacheBlock *CacheSimulator::bringBlockIntoCache(uint32_t address) const {
        /**
         *
         * 1. Use `_cache->get_blocks_in_set` to get all the blocks that could
         *    cache `address`.
         * 2. Loop through all these blocks to find an invalid `block`. If found,
         *    skip to step 4.
         * 3. Loop through all these blocks to find the least recently used `block`.
         *    If the block is dirty, write it back to memory.
         * 4. Update the `block`'s tag. Read data into it from memory. Mark it as
         *    valid. Mark it as clean. Return a pointer to the `block`.
         */
        const CacheConfig &_cache_config = _cache->getCacheConfig();
        uint32_t index = extractIndex(address, _cache_config);

        vector<CacheBlock *> cache_vec = _cache->getBlocksInSet(index);
        uint32_t tag = extractTag(address, _cache_config);

        uint32_t least_recently_used = 1000000;
        uint32_t first_stored_time = 1000000;

        CacheBlock *block = nullptr;

        for (size_t i = 0; i < cache_vec.size(); i++) {
            if (!cache_vec[i]->isValid()) {
                cache_vec[i]->setTag(tag);
                cache_vec[i]->readDataFromMemory(_memory);
                cache_vec[i]->markAsValid();
                cache_vec[i]->markAsClean();
                return cache_vec[i];
            }
            if (_cache_config.getEvictionType() == LRU) {
                if (cache_vec[i]->getLastUsedTime() < least_recently_used) {
                    least_recently_used = cache_vec[i]->getLastUsedTime();
                    block = cache_vec[i];
                }
            } else {
                if (cache_vec[i]->getStoredTime() < first_stored_time) {
                    first_stored_time = cache_vec[i]->getStoredTime();
                    block = cache_vec[i];
                }
            }
        }
        if (block != nullptr) {
            if (block->isDirty()) {
                block->writeDataToMemory(_memory);
            }
            block->setTag(tag);
            block->readDataFromMemory(_memory);
            block->markAsValid();
            block->markAsClean();

            return block;
        }
        return nullptr;
    }

    uint32_t CacheSimulator::read(uint32_t address) const {
        /**
         *
         * 1. Use `find_block` to find the `block` caching `address`.
         * 2. If not found, use `bring_block_into_cache` cache `address` in `block`.
         * 3. Update the `last_used_time` for the `block`.
         * 4. Use `read_word_at_offset` to return the data at `address`.
         */
        _cache->setTotalLoads(_cache->getTotalLoads() + 1);

        CacheBlock *caching = findBlock(address);

        if (!caching) {
            _cache->setLoadMisses(_cache->getLoadMisses() + 1);
            _cache->setTotalCycles(_cache->getTotalCycles() + 1);

            caching = bringBlockIntoCache(address);
        } else {
            _cache->setLoadHits(_cache->getLoadHits() + 1);
        }

        const CacheConfig &_cache_config = _cache->getCacheConfig();
        caching->setLastUsedTime((++_use_clock).getCount());

        return caching->readWordAtOffset(extractBlockOffset(address, _cache_config));
    }

    void CacheSimulator::write(uint32_t address, uint32_t word) const {
        /**
         *
         * 1. Use `find_block` to find the `block` caching `address`.
         * 2. If not found
         *    a. If the policy is write allocate, use `bring_block_into_cache`.
         *    a. Otherwise, directly write the `word` to `address` in the memory
         *       using `_memory->write_word` and return.
         * 3. Update the `last_used_time` for the `block`.
         * 4. Use `write_word_at_offset` to to write `word` to `address`.
         * 5. a. If the policy is write back, mark `block` as dirty.
         *    b. Otherwise, write `word` to `address` in memory.
         */
        _cache->setTotalSets(_cache->getTotalSets() + 1);

        CacheBlock *caching = findBlock(address);
        if (!caching) {
            _cache->setSetMisses(_cache->getSetMisses() + 1);

            if (_cache->getCacheConfig().getAllocation() == WRITE_ALLOCATE) {
                _cache->setTotalCycles(_cache->getTotalCycles() + 1);

                caching = bringBlockIntoCache(address);
            } else {
                _memory->writeWord(address, word);
                return;
            }
        } else {
            _cache->setSetHits(_cache->getSetHits() + 1);
        }

        caching->setLastUsedTime((++_use_clock).getCount());
        caching->setStoredTime((++_use_clock).getCount());

        const CacheConfig &_cache_config = _cache->getCacheConfig();

        caching->writeWordAtOffset(word, extractBlockOffset(address, _cache_config));

        if (_cache_config.getWrite() == WRITE_BACK) {
            caching->markAsDirty();
        } else {
            _cache->setTotalCycles(_cache->getTotalCycles() + _cache->getCacheConfig().getNumBytes() / 4 * 100);
            caching->writeDataToMemory(_memory);
        }
    }

    uint32_t CacheSimulator::getHits() const {
        return _hits.getCount();
    }

    void CacheSimulator::display() {
        cout << "Total loads: " << _cache->getTotalLoads() << "\n";
        cout << "Total stores: " << _cache->getTotalSets() << "\n";
        cout << "Load hits: " << _cache->getLoadHits() << "\n";
        cout << "Load misses: " << _cache->getLoadMisses() << "\n";
        cout << "Store hits: " << _cache->getSetHits() << "\n";
        cout << "Store misses: " << _cache->getSetMisses() << "\n";
        cout << "Total cycles: " << _cache->getTotalCycles() << "\n";
        cout << endl;
    }
}
