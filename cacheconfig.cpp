/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * Steven (Bumjin) Kim
 * bkim63@jhu.edu
 */
#include <iostream>
#include "cacheconfig.h"
#include "utils.h"

using namespace std;

namespace bkim63 {
    unsigned int CacheConfig::getNumSets() const {
        return _num_sets;
    }

    unsigned int CacheConfig::getNumBlocks() const {
        return _num_blocks;
    }

    unsigned int CacheConfig::getNumBytes() const {
        return _num_bytes;
    }

    unsigned int CacheConfig::getSize() const {
        return _size;
    }

    unsigned int CacheConfig::getNumBlockOffsetBits() const {
        return _num_block_offset_bits;
    }

    unsigned int CacheConfig::getNumIndexBits() const {
        return _num_index_bits;
    }

    unsigned int CacheConfig::getNumTagBits() const {
        return _num_tag_bits;
    }

    Allocation CacheConfig::getAllocation() const {
        return _allocation;
    }

    Write CacheConfig::getWrite() const {
        return _write;
    }

    CacheEviction CacheConfig::getEvictionType() const {
        return _eviction_type;
    }

    CacheMapping CacheConfig::getMappingType() const {
        return _mapping_type;
    }

    void CacheConfig::setNumSets(uint32_t numSets) {
        _num_sets = numSets;
    }

    void CacheConfig::setNumBlocks(uint32_t numBlocks) {
        _num_blocks = numBlocks;
    }

    void CacheConfig::setNumBytes(uint32_t numBytes) {
        _num_bytes = numBytes;
    }

    void CacheConfig::setSize(uint32_t size) {
        _size = size;
    }

    void CacheConfig::setNumBlockOffsetBits(uint32_t numBlockOffsetBits) {
        _num_block_offset_bits = numBlockOffsetBits;
    }

    void CacheConfig::setNumIndexBits(uint32_t numIndexBits) {
        _num_index_bits = numIndexBits;
    }

    void CacheConfig::setNumTagBits(uint32_t numTagBits) {
        _num_tag_bits = numTagBits;
    }

    void CacheConfig::setAllocation(Allocation allocation) {
        _allocation = allocation;
    }

    void CacheConfig::setWrite(Write write) {
        _write = write;
    }

    void CacheConfig::setEvictionType(CacheEviction evictionType) {
        _eviction_type = evictionType;
    }

    void CacheConfig::setMappingType(CacheMapping mappingType) {
        _mapping_type = mappingType;
    }

    void CacheConfig::setCacheMapping(uint32_t num_blocks, uint32_t num_sets) {
        if (num_blocks == 1 && num_sets > 1)
            _mapping_type = DIRECT_MAPPED;
        else if (num_blocks > 1 && num_sets > 1)
            _mapping_type = SET_ASSOCIATIVE;
        else if (num_sets == 1 && num_blocks > 1)
            _mapping_type = FULLY_ASSOCIATIVE;
    }

    CacheConfig::CacheConfig(uint32_t size, uint32_t numSets, uint32_t numBlocks, uint32_t numBytes,
                             Allocation allocation, Write write, CacheEviction evictionType) :
            _size(size), _num_sets(numSets), _num_blocks(numBlocks), _num_bytes(numBytes),
            _allocation(allocation), _write(write), _eviction_type(evictionType) {

        setCacheMapping(numBlocks, numSets);

        _associativity = _mapping_type == DIRECT_MAPPED ? 1 : _num_blocks;

        _num_block_offset_bits = log2(_num_bytes);

        uint32_t index = (size / (_associativity * _num_bytes));

        _num_index_bits = log2(index);

        _num_tag_bits = 32 - _num_index_bits - _num_block_offset_bits;
    }

    uint32_t CacheConfig::getAssociativity() const {
        return _associativity;
    }

    void CacheConfig::setAssociativity(uint32_t associativity) {
        _associativity = associativity;
    }

}
