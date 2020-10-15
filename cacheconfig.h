/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 * 2. Rebecca Shao
 */

#ifndef CACHE_CONFIG_H
#define CACHE_CONFIG_H

#include <cstdint>

namespace bkim63 {
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

        uint32_t _num_sets;
        uint32_t _num_blocks;
        uint32_t _num_bytes;

        uint32_t _num_block_offset_bits;
        uint32_t _num_index_bits;
        uint32_t _num_tag_bits;
        uint32_t _associativity;

        Allocation _allocation;
        Write _write;

        CacheEviction _eviction_type;
        CacheMapping _mapping_type;

        void setCacheMapping(uint32_t, uint32_t);

    public:
        CacheConfig(uint32_t size, uint32_t numSets, uint32_t numBlocks, uint32_t numBytes, Allocation allocation, Write write,
                    CacheEviction evictionType);

        uint32_t getAssociativity() const;

        void setAssociativity(uint32_t associativity);

        uint32_t getNumSets() const;

        void setNumSets(uint32_t numSets);

        void setNumBlocks(uint32_t numBlocks);

        void setNumBytes(uint32_t numBytes);

        void setSize(uint32_t size);

        void setNumBlockOffsetBits(uint32_t numBlockOffsetBits);

        void setNumIndexBits(uint32_t numIndexBits);

        void setNumTagBits(uint32_t numTagBits);

        void setAllocation(Allocation allocation);

        void setWrite(Write write);

        void setEvictionType(CacheEviction evictionType);

        void setMappingType(CacheMapping mappingType);

        uint32_t getNumBlocks() const;

        uint32_t getNumBytes() const;

        uint32_t getSize() const;

        uint32_t getNumBlockOffsetBits() const;

        uint32_t getNumIndexBits() const;

        uint32_t getNumTagBits() const;

        Allocation getAllocation() const;

        Write getWrite() const;

        CacheEviction getEvictionType() const;

        CacheMapping getMappingType() const;
    };
}
#endif
