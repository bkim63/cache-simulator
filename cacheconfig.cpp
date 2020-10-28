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
    /* 
     * Getter for number of sets in cache configuration
     * 
     * Returns:
     *  unsigned int number of sets
     */
    unsigned int CacheConfig::getNumSets() const {
        return _numSets;
    }

    /* 
     * Getter for number of blocks in cache configuration
     * 
     * Returns:
     *  unsigned int number of blocks
     */
    unsigned int CacheConfig::getNumBlocks() const {
        return _numBlocks;
    }

    /* 
     * Getter for number of bytes in cache configuration
     * 
     * Returns:
     *  unsigned int number of bytes
     */
    unsigned int CacheConfig::getNumBytes() const {
        return _numBytes;
    }

    /* 
     * Getter for number of offset bits in cache configuration
     * 
     * Returns:
     *  unsigned int number of offsett bits
     */
    unsigned int CacheConfig::getNumBlockOffsetBits() const {
        return _numBlockOffsetBits;
    }

    /* 
     * Getter for number of index bits in cache configuration
     * 
     * Returns:
     *  unsigned int number of index bits
     */
    unsigned int CacheConfig::getNumIndexBits() const {
        return _numIndexBits;
    }

    /* 
     * Getter for number of tag bits in cache configuration
     * 
     * Returns:
     *  unsigned int number of tag bits
     */
    unsigned int CacheConfig::getNumTagBits() const {
        return _numTagBits;
    }

    /* 
     * Getter of write-miss method of cache configuration
     * 
     * Returns:
     *  Allocation to indicate write miss method 
     */
    Allocation CacheConfig::getAllocation() const {
        return _allocation;
    }

    /* 
     * Getter for write-hit method of cache configuration
     * 
     * Returns:
     *  Write to indicate write hit method 
     */
    Write CacheConfig::getWrite() const {
        return _write;
    }

    /* 
     * Getter for cache eviction technique for cache configuration
     * 
     * Returns:
     *  CacheEviction to indicate cache eviction method
     */
    CacheEviction CacheConfig::getEvictionType() const {
        return _evictionType;
    }

    /* 
     * Getter for cache mapping type for cache configuration
     * 
     * Returns:
     *  CacheMapping to indicate cache mapping method
     */
    CacheMapping CacheConfig::getMappingType() const {
        return _mappingType;
    }

    /* 
     * Setter for number of sets in cache configuration
     * 
     * Parameters:
     *  numSets - uint32_t to set _numSets to 
     */
    void CacheConfig::setNumSets(uint32_t numSets) {
        _numSets = numSets;
    }

    /* 
     * Setter for number of blocks in cache configuration
     * 
     * Parameters:
     *  numBlocks - uint32_t to set numBlocks to 
     */
    void CacheConfig::setNumBlocks(uint32_t numBlocks) {
        _numBlocks = numBlocks;
    }

    /* 
     * Setter for number of bytes in cache configuration
     * 
     * Parameters:
     *  numBytes - uint32_t to set numBytes to 
     */
    void CacheConfig::setNumBytes(uint32_t numBytes) {
        _numBytes = numBytes;
    }

    /* 
     * Setter for number of offset bits in cache configuration
     * 
     * Parameters:
     *  numBlockOffsetBits - uint32_t to set _numBlockOffsetBits to 
     */
    void CacheConfig::setNumBlockOffsetBits(uint32_t numBlockOffsetBits) {
        _numBlockOffsetBits = numBlockOffsetBits;
    }

    /* 
     * Setter for number of index bits in cache configuration
     * 
     * Parameters:
     *  numIndexBits - uint32_t to set _numIndexBits to 
     */
    void CacheConfig::setNumIndexBits(uint32_t numIndexBits) {
        _numIndexBits = numIndexBits;
    }

    /* 
     * Setter for number of tag bits in cache configuration
     * 
     * Parameters:
     *  numTagBits - uint32_t to set _numTagBits to 
     */
    void CacheConfig::setNumTagBits(uint32_t numTagBits) {
        _numTagBits = numTagBits;
    }

    /* 
     * Setter for allocation method for cache config
     * 
     * Parameters:
     *  allocation - Allocation to set _allocation to 
     */
    void CacheConfig::setAllocation(Allocation allocation) {
        _allocation = allocation;
    }

    /* 
     * Setter for write-hit method for cache config
     * 
     * Parameters:
     *  write - Write to set _write to 
     */
    void CacheConfig::setWrite(Write write) {
        _write = write;
    }

    /* 
     * Setter for eviction method for cache config
     * 
     * Parameters:
     *  evictionType - CacheEviction to set _evictionType to 
     */
    void CacheConfig::setEvictionType(CacheEviction evictionType) {
        _evictionType = evictionType;
    }

    /* 
     * Setter for mapping type for cache config
     * 
     * Parameters:
     *  mappingType - CacheMapping to set _mappingType to 
     */
    void CacheConfig::setMappingType(CacheMapping mappingType) {
        _mappingType = mappingType;
    }

    /* 
     * Function to set cache mapping
     * 
     * Parameters:
     *  numBlocks - uint32_t number of blocks in cache config
     *  numSets - uint32_t number of sets in cache config
     */
    void CacheConfig::setCacheMapping(uint32_t numBlocks, uint32_t numSets) {
        if (numBlocks == 1 && numSets > 1)
            _mappingType = DIRECT_MAPPED;
        else if (numBlocks > 1 && numSets > 1)
            _mappingType = SET_ASSOCIATIVE;
        else if (numSets == 1 && numBlocks > 1)
            _mappingType = FULLY_ASSOCIATIVE;
    }

    /* 
     * Constructor for CacheConfig class
     */
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

    /* 
     * Getter for associativity of cache
     * 
     * Returns:
     *  uint32_t that is the associativity of cache
     */
    uint32_t CacheConfig::getAssociativity() const {
        return _associativity;
    }

    /* 
     * Setter for associativity of cache
     * 
     * Parameters:
     *  associativity - uint32_t to set _associativity field to
     */
    void CacheConfig::setAssociativity(uint32_t associativity) {
        _associativity = associativity;
    }

}
