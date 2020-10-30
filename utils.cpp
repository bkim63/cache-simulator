/**
 * CSF Fall 2020
 * Cache helper function implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <bitset>
#include "utils.h"

#define numBits 32

/*
 * Utils Class with useful helper functions for cache implementation.
 */
namespace CacheSimulator {
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
    void displaySimulator(int loadHits, int loadMisses, int storeHits, int storeMisses, int totalCycles) {
        std::cout << "Total loads: " << (loadHits + loadMisses) << std::endl;
        std::cout << "Total stores: " << (storeHits + storeMisses) << std::endl;
        std::cout << "Load hits: " << loadHits << std::endl;
        std::cout << "Load misses: " << loadMisses << std::endl;
        std::cout << "Store hits: " << storeHits << std::endl;
        std::cout << "Store misses: " << storeMisses << std::endl;
        std::cout << "Total cycles: " << totalCycles << std::endl;
    }

    /* 
     * Function to get the power two of parameter value
     * 
     * Parameters:
     *  val - int to get power two of
     */
    int getPowerTwo(int val) {
        int exp = (int) (log(val) / log(2));

        if (pow(2, exp) == val)
            return exp;
        else {
            std::cerr << "The arguments should be a power of 2" << std::endl;
            return -1;
        }
    }

    /* 
     * Function to convert string into integer
     * 
     * Parameters:
     *  argument - string to be converted into an integer
     * 
     * Returns:
     *  int to indicate success
     */
    int convertToInteger(std::string argument) {
        int value = -1;
        try {
            value = stoi(argument);
        } catch (std::invalid_argument &e) {
            std::cerr << "Invalid argument" << std::endl;
            return -1;
        } catch (std::out_of_range &e) {
            std::cerr << "Out of range" << std::endl;
            return -1;
        }

        value = std::stoi(argument);

        if (value <= 0) {
            std::cerr << "The argument must be greater than 0" << std::endl;
            return -1;
        }
        return 0;
    }

    /* 
     * Function to get cache miss strategy
     * 
     * Parameters:
     *  argument - string to indicate which miss strategy to use
     * 
     * Returns:
     *  int to indicate cache miss strategy
     */
    int getCacheMissStrategy(std::string argument) {
        if (argument.compare("write-allocate") == 0)
            return 0;
        else if (argument.compare("no-write-allocate") == 0)
            return 1;
        else {
            std::cerr << "Invalid parameter" << std::endl;
            return -1;
        }
    }

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
    std::string getIndex(int indexSize, int tagSize, unsigned int address) {
        std::bitset<numBits> bitAddress(address);
        std::string index = bitAddress.to_string();

        return index.substr(tagSize, indexSize);
    }

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
    std::string getTag(int tagSize, unsigned int address) {
        std::bitset<numBits> bitTag(address);
        std::string tag = bitTag.to_string();

        return tag.substr(0, tagSize);
    }

    /* 
     * Function to get cache write strategy
     * 
     * Parameters:
     *  argument - string to indicate which write strategy to use
     * 
     * Returns:
     *  int to indicate cache write strategy
     */
    int getCacheWriteStrategy(std::string argument) {
        if (argument.compare("write-through") == 0)
            return 0;
        else if (argument.compare("write-back") == 0)
            return 1;
        else {
            std::cerr << "Invalid parameter" << std::endl;
            return -1;
        }
    }

    /* 
     * Function to get eviction strategy
     * 
     * Parameters:
     *  argument - string to indicate which eviction to use
     * 
     * Returns:
     *  int to indicate eviction strategy
     */
    int shouldEvict(std::string argument) {
        if (argument.compare("lru") == 0)
            return 0;
        else if (argument.compare("fifo") == 0)
            return 1;
        else {
            std::cerr << "Invalid strategy" << std::endl;
            return -1;
        }
    }

}