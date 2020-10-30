/**
 * CSF Fall 2020
 * Cache config function and data type declarations
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#ifndef CACHE_CONFIG_H
#define CACHE_CONFIG_H

#include <cstdint>

/* 
 * CacheConfig class whose instance is the cache configuration.
 */
namespace CacheSimulator {
    enum Allocation {
        WRITE_ALLOCATE,
        NO_WRITE_ALLOCATE
    };

    enum Write {
        WRITE_THROUGH,
        WRITE_BACK
    };

    enum CacheEviction {
        LRU,
        FIFO
    };

    enum CacheMapping {
        DIRECT_MAPPED = 1,
        SET_ASSOCIATIVE = 2,
        FULLY_ASSOCIATIVE = 3
    };

    class CacheConfig {
        uint32_t _size;

        uint32_t _numSets;
        uint32_t _numBlocks;
        uint32_t _numBytes;

        uint32_t _numBlockOffsetBits;
        uint32_t _numIndexBits;
        uint32_t _numTagBits;
        uint32_t _associativity;

        Allocation _allocation;
        Write _write;

        CacheEviction _evictionType;
        CacheMapping _mappingType;

        /* 
        * Function to set cache mapping
        * 
        * Parameters:
        *  numBlocks - uint32_t number of blocks in cache config
        *  numSets - uint32_t number of sets in cache config
        */
        void setCacheMapping(uint32_t, uint32_t);

    public:
        /* 
        * Constructor for CacheConfig class
        * 
        * Parameters:
        *  uint32_t numSets number of sets in cache
        *  uint32_t numBlocks number of blocks in cache
        *  uint32_t numBytes number of byte in cache
        *  Allocation allocation - allocation of cache
        *  Write write - write method of cache
        *  CacheEviction evictionType - eviction method of cache
        */
        CacheConfig(uint32_t numSets, uint32_t numBlocks, uint32_t numBytes, 
                    Allocation allocation, Write write, CacheEviction evictionType);

        /* 
        * Getter for associativity of cache
        * 
        * Returns:
        *  uint32_t that is the associativity of cache
        */
        uint32_t getAssociativity() const;

        /* 
        * Setter for associativity of cache
        * 
        * Parameters:
        *  associativity - uint32_t to set _associativity field to
        */
        void setAssociativity(uint32_t associativity);

        /* 
        * Getter for number of sets in cache configuration
        * 
        * Returns:
        *  unsigned int number of sets
        */
        uint32_t getNumSets() const;
    
        /* 
        * Setter for number of sets in cache configuration
        * 
        * Parameters:
        *  numSets - uint32_t to set _numSets to 
        */
        void setNumSets(uint32_t numSets);

        /* 
        * Setter for number of blocks in cache configuration
        * 
        * Parameters:
        *  numBlocks - uint32_t to set numBlocks to 
        */
        void setNumBlocks(uint32_t numBlocks);

        /* 
        * Setter for number of bytes in cache configuration
        * 
        * Parameters:
        *  numBytes - uint32_t to set numBytes to 
        */
        void setNumBytes(uint32_t numBytes);


        void setSize(uint32_t size);

        /* 
        * Setter for number of offset bits in cache configuration
        * 
        * Parameters:
        *  numBlockOffsetBits - uint32_t to set _numBlockOffsetBits to 
        */
        void setNumBlockOffsetBits(uint32_t numBlockOffsetBits);

        /* 
        * Setter for number of index bits in cache configuration
        * 
        * Parameters:
        *  numIndexBits - uint32_t to set _numIndexBits to 
        */
        void setNumIndexBits(uint32_t numIndexBits);

        /* 
        * Setter for number of tag bits in cache configuration
        * 
        * Parameters:
        *  numTagBits - uint32_t to set _numTagBits to 
        */
        void setNumTagBits(uint32_t numTagBits);

        /* 
        * Setter for allocation method for cache config
        * 
        * Parameters:
        *  allocation - Allocation to set _allocation to 
        */
        void setAllocation(Allocation allocation);

        /* 
        * Setter for write-hit method for cache config
        * 
        * Parameters:
        *  write - Write to set _write to 
        */
        void setWrite(Write write);

        /* 
        * Setter for eviction method for cache config
        * 
        * Parameters:
        *  evictionType - CacheEviction to set _evictionType to 
        */
        void setEvictionType(CacheEviction evictionType);

        /* 
        * Setter for mapping type for cache config
        * 
        * Parameters:
        *  mappingType - CacheMapping to set _mappingType to 
        */
        void setMappingType(CacheMapping mappingType);

        /* 
        * Getter for number of blocks in cache configuration
        * 
        * Returns:
        *  unsigned int number of blocks
        */
        uint32_t getNumBlocks() const;

        /* 
        * Getter for number of bytes in cache configuration
        * 
        * Returns:
        *  unsigned int number of bytes
        */
        uint32_t getNumBytes() const;

        uint32_t getSize() const;

        /* 
        * Getter for number of offset bits in cache configuration
        * 
        * Returns:
        *  unsigned int number of offsett bits
        */
        uint32_t getNumBlockOffsetBits() const;

        /* 
        * Getter for number of index bits in cache configuration
        * 
        * Returns:
        *  unsigned int number of index bits
        */
        uint32_t getNumIndexBits() const;

        /* 
        * Getter for number of tag bits in cache configuration
        * 
        * Returns:
        *  unsigned int number of tag bits
        */
        uint32_t getNumTagBits() const;

        /* 
        * Getter of write-miss method of cache configuration
        * 
        * Returns:
        *  Allocation to indicate write miss method 
        */
        Allocation getAllocation() const;

        /* 
        * Getter for write-hit method of cache configuration
        * 
        * Returns:
        *  Write to indicate write hit method 
        */
        Write getWrite() const;

        /* 
        * Getter for cache eviction technique for cache configuration
        * 
        * Returns:
        *  CacheEviction to indicate cache eviction method
        */
        CacheEviction getEvictionType() const;

        /* 
        * Getter for cache mapping type for cache configuration
        * 
        * Returns:
        *  CacheMapping to indicate cache mapping method
        */
        CacheMapping getMappingType() const;
    };
}
#endif
