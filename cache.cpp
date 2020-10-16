/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#include "cache.h"
#include "cacheconfig.h"
#include "cacheblock.h"

namespace CacheSimulator {
    Cache::Cache(CacheConfig &cacheConfig) : _cache_config(cacheConfig) {
        _total_loads = 0;
        _total_sets = 0;

        _load_hits = 0;
        _load_misses = 0;

        _set_hits = 0;
        _set_misses = 0;

        _total_cycles = 0;

        initBlocks();
    }

    int Cache::getTotalLoads() const {
        return _total_loads;
    }

    void Cache::setTotalLoads(int totalLoads) {
        _total_loads = totalLoads;
    }

    int Cache::getTotalSets() const {
        return _total_sets;
    }

    void Cache::setTotalSets(int totalSets) {
        _total_sets = totalSets;
    }

    int Cache::getLoadHits() const {
        return _load_hits;
    }

    void Cache::setLoadHits(int loadHits) {
        _load_hits = loadHits;
    }

    int Cache::getLoadMisses() const {
        return _load_misses;
    }

    void Cache::setLoadMisses(int loadMisses) {
        _load_misses = loadMisses;
    }

    int Cache::getSetHits() const {
        return _set_hits;
    }

    void Cache::setSetHits(int setHits) {
        _set_hits = setHits;
    }

    int Cache::getSetMisses() const {
        return _set_misses;
    }

    void Cache::setSetMisses(int setMisses) {
        _set_misses = setMisses;
    }

    int Cache::getTotalCycles() const {
        return _total_cycles;
    }

    void Cache::setTotalCycles(int totalCycles) {
        _total_cycles = totalCycles;
    }

    void Cache::setCacheConfig(CacheConfig &cacheConfig) {
        _cache_config = cacheConfig;
    }

    std::vector<CacheBlock *> Cache::getBlocksInSet(uint32_t index) const {
        uint32_t num_sets = _cache_config.getSize() / _cache_config.getNumBytes() / _cache_config.getAssociativity();

        assert(index < num_sets);

        std::__wrap_iter<CacheBlock *const *> first_block = _blocks.begin() + (index * _cache_config.getAssociativity());
        std::__wrap_iter<CacheBlock *const *> last_block = first_block + _cache_config.getAssociativity();

        std::vector<CacheBlock *> set(first_block, last_block);
        return set;
    }

    void Cache::initBlocks() {
        uint32_t num_blocks = _cache_config.getSize() / _cache_config.getNumBytes();

        for (uint32_t i = 0; i < num_blocks; ++i) {
            uint32_t index = i / _cache_config.getAssociativity();
            CacheBlock *block = new CacheBlock(index, _cache_config);
            _blocks.push_back(block);
        }
    }

    Cache::~Cache() {
        for (size_t i = 0; i < _blocks.size(); i++) {
            delete _blocks[i];
        }
    }

    CacheConfig &Cache::getCacheConfig() const {
        return _cache_config;
    }

    void Cache::setCacheConfig1(CacheConfig &cacheConfig) {
        _cache_config = cacheConfig;
    }

}
