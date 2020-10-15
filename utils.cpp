/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * Steven (Bumjin) Kim
 * bkim63@jhu.edu
 */
#include <sstream>
#include <iostream>
#include "utils.h"

using namespace std;

namespace bkim63 {

    uint32_t extractTag(uint32_t address, const CacheConfig &cache_config) {
        uint32_t offset_bits = cache_config.getNumBlockOffsetBits();
        uint32_t index_bits = cache_config.getNumIndexBits();
        uint32_t tag_bits = cache_config.getNumTagBits();

        if (tag_bits > 31) {
            return address;
        }
        return (address >> (offset_bits + index_bits));
    }

    uint32_t extractIndex(uint32_t address, const CacheConfig &cache_config) {
//        cout << "load miss: " << address << endl;

        uint32_t offset_bits = cache_config.getNumBlockOffsetBits();
        // uint32_t index_bits = cache_config.get_num_index_bits();
        uint32_t tag_bits = cache_config.getNumTagBits();

//        cout << "load miss: " << offset_bits << " " << tag_bits << endl;

        if (tag_bits > 31) {
            return 0;
        }

        return ((address << tag_bits) >> (tag_bits + offset_bits));
    }

    uint32_t extractBlockOffset(uint32_t address, const CacheConfig &cache_config) {
        // uint32_t offset_bits = cache_config.get_num_block_offset_bits();
        uint32_t index_bits = cache_config.getNumIndexBits();
        uint32_t tag_bits = cache_config.getNumTagBits();

        if (tag_bits > 31) {
            return 0;
        }

        uint32_t tag_ind = tag_bits + index_bits;
        return ((address << tag_ind) >> tag_ind);
    }

    bool isPowerOf2(uint32_t num) {
        return num != 0 && (num & (num - 1)) == 0;
    }

    uint32_t log2(uint32_t num) {
        assert(isPowerOf2(num));
        return 31 - __builtin_clz(num);
    }
}
