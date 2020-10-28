/**
 * CSF Fall 2020
 * Main file
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#include "utils.h"
#include "cacheset.h"
#include "cacheblock.h"
#include "cache.h"

#include <sstream>
#include <string>
#include <cstring>

/* 
 * Function to print messages about cache 
 */
void printHelp() {
    std::cout << "No proper argument passed to program\n";
    std::cout << "Usage: " << "./csim <number-of-sets>"
              << " <number-of-blocks>"
              << " <number-of-bytes>"
              << " <allocation>"
              << " <write>"
              << " <cache-eviction>"
              << " < <filename>\n";
}

int main(int argc, char *argv[]) {

    int numSets = 0;
    int numBlocks = 0;
    int blockSize = 0;
    int cacheStore = 0;
    int memoryWrite = 0;
    int evict = 0;

    if (argc == 7) {
        // arguments check
        numBlocks = std::stoi(argv[2]);
        int check = CacheSimulator::convertToInteger(argv[3]);
        if (check == -1)
            return 1;

        check = CacheSimulator::convertToInteger(argv[1]);
        if (check == -1)
            return 1;

        numSets = std::stoi(argv[1]);
        check = CacheSimulator::convertToInteger(argv[2]);
        if (check == -1)
            return 1;

        blockSize = std::stoi(argv[3]);
        if (blockSize < 4) {
            std::cerr << "The number of bytes must be greater than or equal to 4 bytes" << std::endl;
            printHelp();
            return 1;
        }

        memoryWrite = CacheSimulator::getCacheWriteStrategy(argv[5]);
        if (memoryWrite == -1)
            return 1;

        cacheStore = CacheSimulator::getCacheMissStrategy(argv[4]);
        if (cacheStore == -1)
            return 1;

        if (cacheStore == 1 && memoryWrite == 1) {
            std::cerr << "Cannot simulate no-write-allocate and write-back at the same time" << std::endl;
            printHelp();
            return 1;
        }

        evict = CacheSimulator::shouldEvict(argv[6]);
        if (evict == -1)
            return 1;


        int numBitIndex = CacheSimulator::getPowerTwo(numSets);
        int numBitOffset = CacheSimulator::getPowerTwo(blockSize);

        if (numBitIndex == -1 || numBitOffset == -1)
            return 1;


        int numBitTag = 32 - numBitOffset - numBitIndex;

        CacheSimulator::Cache cache = CacheSimulator::Cache(numSets, numBlocks, blockSize, cacheStore, memoryWrite, evict);
        std::string firstTag = "";

        bool dirty = false;
        bool noErr = false;

        for (std::string line; getline(std::cin, line);) {
            uint32_t address, data;
            std::string operation;
            std::istringstream string_stream(line);

            string_stream >> operation >> std::hex >> address >> std::dec >> data;

            std::string index = CacheSimulator::getIndex(numBitIndex, numBitTag, address);
            std::string tag = CacheSimulator::getTag(numBitTag, address);

            if (operation == "l") {
                // read from cache
                check = cache.read(index, tag, firstTag);
                if (check != 0) {
                    std::cerr << "Failed to read from cache." << std::endl;
                    return 1;
                }
            } else if (operation == "s") {
                // write to cache
                check = cache.write(index, tag, firstTag, dirty);
                if (check == -1) {
                    std::cerr << "Failed to write to cache." << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "Invalid operation" << std::endl;
                printHelp();
                return 1;
            }
            CacheSimulator::CacheSet *set = cache.findSet(index);

            if (set->getNumBlocksStored() == 0) {
                CacheSimulator::CacheBlock *block = new CacheSimulator::CacheBlock(tag);
                if (dirty) {
                    dirty = false;
                    block->setDirty();
                }
                cache.findSet(index)->addBlock(*block);
                delete block;
            }

            noErr = true;
        }

        if (!noErr && firstTag.compare("") != 0) {
            std::cerr << "Failed tracing" << std::endl;
            printHelp();
            return 1;
        }

        cache.displaySimulator();
        return 0;

    } else {
        printHelp();
        return 1;
    }

}
