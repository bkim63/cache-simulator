/**
 * CSF Fall 2020
 * Cache counter implementation
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

namespace CacheSimulator {
    int getPowerTwo(int val);

    int convertToInteger(std::string argument);

    int getCacheMissStrategy(std::string argument);

    int getCacheWriteStrategy(std::string argument);

    int shouldEvict(std::string argument);

    std::string getIndex(int indexSize, int tagSize, unsigned int address);

    std::string getTag(int tagSize, unsigned int address);

    void displaySimulator(int loadHits, int loadMisses, int storeHits, int storeMisses, int totalCycles);
}

#endif
