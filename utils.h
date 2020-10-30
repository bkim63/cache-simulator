/**
 * CSF Fall 2020
 * Cache utility function declaration
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <stdlib.h>
#include <math.h>

/*
 * Utils Class with useful helper functions for cache implementation.
 */
namespace CacheSimulator {
    /* 
     * Function to get the power two of parameter value
     * 
     * Parameters:
     *  val - int to get power two of
     */
    int getPowerTwo(int val);

    /* 
     * Function to convert string into integer
     * 
     * Parameters:
     *  argument - string to be converted into an integer
     * 
     * Returns:
     *  int to indicate success
     */
    int convertToInteger(std::string argument);

    /* 
     * Function to get cache miss strategy
     * 
     * Parameters:
     *  argument - string to indicate which miss strategy to use
     * 
     * Returns:
     *  int to indicate cache miss strategy
     */
    int getCacheMissStrategy(std::string argument);

    /* 
     * Function to get cache write strategy
     * 
     * Parameters:
     *  argument - string to indicate which write strategy to use
     * 
     * Returns:
     *  int to indicate cache write strategy
     */
    int getCacheWriteStrategy(std::string argument);

    /* 
     * Function to get eviction strategy
     * 
     * Parameters:
     *  argument - string to indicate which eviction to use
     * 
     * Returns:
     *  int to indicate eviction strategy
     */
    int shouldEvict(std::string argument);

    /* 
     * Function to get index
     * 
     * Parameters:
     *  indexSize - int that is the index size
     *  tagSize - int that is tag size
     *  address - unsigned int that is address
     * 
     * Returns:
     *  string that is the index
     */
    std::string getIndex(int indexSize, int tagSize, unsigned int address);

    /* 
     * Function to get tag
     * 
     * Parameters:
     *  tagSize - int that is tag size
     *  address - unsigned int that is address
     * 
     * Returns:
     *  string that is the tag
     */
    std::string getTag(int tagSize, unsigned int address);

    /* 
     * Function to print the load and store information of cache
     * 
     * Parameters:
     *  loadHits - int that is number of load hits
     *  loadMisses - int that is number of load misses
     *  storeHits - int that is number of store hits
     *  storeMisses - int that is number of store misses
     *  totalCycle - int that is total number of cycles
     */
    void displaySimulator(int loadHits, int loadMisses, int storeHits, int storeMisses, int totalCycles);
}

#endif
