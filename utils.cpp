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

namespace CacheSimulator {

    void displaySimulator(int loadHits, int loadMisses, int storeHits, int storeMisses, int totalCycles) {
        std::cout << "Total loads: " << (loadHits + loadMisses) << std::endl;
        std::cout << "Total stores: " << (storeHits + storeMisses) << std::endl;
        std::cout << "Load hits: " << loadHits << std::endl;
        std::cout << "Load misses: " << loadMisses << std::endl;
        std::cout << "Store hits: " << storeHits << std::endl;
        std::cout << "Store misses: " << storeMisses << std::endl;
        std::cout << "Total cycles: " << totalCycles << std::endl;
    }

    int getPowerTwo(int val) {
        int exp = (int) (log(val) / log(2));

        if (pow(2, exp) == val)
            return exp;
        else {
            std::cerr << "The arguments should be a power of 2" << std::endl;
            return -1;
        }
    }

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

    std::string getIndex(int indexSize, int tagSize, unsigned int address) {
        std::bitset<numBits> bitAddress(address);
        std::string index = bitAddress.to_string();

        return index.substr(tagSize, indexSize);
    }

    std::string getTag(int tagSize, unsigned int address) {
        std::bitset<numBits> bitTag(address);
        std::string tag = bitTag.to_string();

        return tag.substr(0, tagSize);
    }

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