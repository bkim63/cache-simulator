/**
 * CSF Fall 2020
 * Cache configuration function implementations
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#include "cacheconfig.h"
#include "utils.h"

using namespace std;

namespace CacheSimulator {
    unsigned int CacheConfig::getNumSets() const {
        return _numSets;
    }

    unsigned int CacheConfig::getNumBlocks() const {
        return _numBlocks;
    }

    unsigned int CacheConfig::getNumBytes() const {
        return _numBytes;
    }

    unsigned int CacheConfig::getNumBlockOffsetBits() const {
        return _numBlockOffsetBits;
    }

    unsigned int CacheConfig::getNumIndexBits() const {
        return _numIndexBits;
    }

    unsigned int CacheConfig::getNumTagBits() const {
        return _numTagBits;
    }

    Allocation CacheConfig::getAllocation() const {
        return _allocation;
    }

    Write CacheConfig::getWrite() const {
        return _write;
    }

    CacheEviction CacheConfig::getEvictionType() const {
        return _evictionType;
    }

    CacheMapping CacheConfig::getMappingType() const {
        return _mappingType;
    }

    void CacheConfig::setNumSets(uint32_t numSets) {
        _numSets = numSets;
    }

    void CacheConfig::setNumBlocks(uint32_t numBlocks) {
        _numBlocks = numBlocks;
    }

    void CacheConfig::setNumBytes(uint32_t numBytes) {
        _numBytes = numBytes;
    }

    void CacheConfig::setNumBlockOffsetBits(uint32_t numBlockOffsetBits) {
        _numBlockOffsetBits = numBlockOffsetBits;
    }

    void CacheConfig::setNumIndexBits(uint32_t numIndexBits) {
        _numIndexBits = numIndexBits;
    }

    void CacheConfig::setNumTagBits(uint32_t numTagBits) {
        _numTagBits = numTagBits;
    }

    void CacheConfig::setAllocation(Allocation allocation) {
        _allocation = allocation;
    }

    void CacheConfig::setWrite(Write write) {
        _write = write;
    }

    void CacheConfig::setEvictionType(CacheEviction evictionType) {
        _evictionType = evictionType;
    }

    void CacheConfig::setMappingType(CacheMapping mappingType) {
        _mappingType = mappingType;
    }

    void CacheConfig::setCacheMapping(uint32_t numBlocks, uint32_t numSets) {
        if (numBlocks == 1 && numSets > 1)
            _mappingType = DIRECT_MAPPED;
        else if (numBlocks > 1 && numSets > 1)
            _mappingType = SET_ASSOCIATIVE;
        else if (numSets == 1 && numBlocks > 1)
            _mappingType = FULLY_ASSOCIATIVE;
    }

    CacheConfig::CacheConfig(uint32_t numSets, uint32_t numBlocks, uint32_t numBytes,
                             Allocation allocation, Write write, CacheEviction evictionType) :
            _numSets(numSets), _numBlocks(numBlocks), _numBytes(numBytes),
            _allocation(allocation), _write(write), _evictionType(evictionType) {

        setCacheMapping(numBlocks, numSets);

        _associativity = _mappingType == DIRECT_MAPPED ? 1 : _numBlocks;
        _numBlockOffsetBits = log2(_numBytes);

        uint32_t index = (_numBytes * numSets * numBlocks) / (_associativity * _numBytes);

        _numIndexBits = log2(index);
        _numTagBits = 32 - _numIndexBits - _numBlockOffsetBits;
    }

    uint32_t CacheConfig::getAssociativity() const {
        return _associativity;
    }

    void CacheConfig::setAssociativity(uint32_t associativity) {
        _associativity = associativity;
    }

}
