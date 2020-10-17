/**
 * CSF Fall 2020
<<<<<<< HEAD
 * Header file for general helper functions
=======
 * Cache utility function declarations
>>>>>>> e7b8c88eb752cb64fc26e456ef9abe94cc893046
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#ifndef UTILS_H
#define UTILS_H

#include <cassert>
#include <cstdint>
#include "cacheconfig.h"


namespace CacheSimulator {
    uint32_t getTag(uint32_t address, const CacheConfig &cache_config);

    uint32_t getIndex(uint32_t address, const CacheConfig &cache_config);

    uint32_t getBlockOffset(uint32_t address, const CacheConfig &cache_config);

    bool isPowerOf2(uint32_t num);
    
    uint32_t log2(uint32_t num);
}

#endif
