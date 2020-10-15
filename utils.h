/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * Steven (Bumjin) Kim
 * bkim63@jhu.edu
 */
#ifndef UTILS_H
#define UTILS_H

#include <cassert>
#include <cstdint>
#include "cacheconfig.h"

using std::uint32_t;

namespace bkim63 {
    uint32_t extractTag(uint32_t address, const CacheConfig &cache_config);

    uint32_t extractIndex(uint32_t address, const CacheConfig &cache_config);

    uint32_t extractBlockOffset(uint32_t address, const CacheConfig &cache_config);

    bool isPowerOf2(uint32_t num);
    
    uint32_t log2(uint32_t num);

}

#endif
