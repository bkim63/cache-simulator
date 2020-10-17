/**
 * CSF Fall 2020
<<<<<<< HEAD
 * Main function to read trace from input and call cache simulator for simulation
=======
 * Cache main implementation
>>>>>>> e7b8c88eb752cb64fc26e456ef9abe94cc893046
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#include <sstream>
#include "cachesimulator.h"
#include <string>

void printHelp();

<<<<<<< HEAD
int main(int argc, char *argv[]) {

    if (argc == 7) {
        /* we got right number of arguments so process them */
        uint32_t num_sets = strtoul(argv[1], NULL, 10);
        uint32_t num_blocks = strtoul(argv[2], NULL, 10);
        uint32_t num_bytes = strtoul(argv[3], NULL, 10);
=======
CacheSimulator::CacheConfig getConfig(char *const *argv);
>>>>>>> e7b8c88eb752cb64fc26e456ef9abe94cc893046

void displaySimulator(CacheSimulator::Memory &memory, CacheSimulator::CacheSimulator *cacheSimulator);

int main(int argc, char *argv[]) {
    if (argc == 7) {
        CacheSimulator::CacheConfig cacheConfig = getConfig(argv);
        CacheSimulator::Cache cache(cacheConfig);
        CacheSimulator::Memory memory;

        CacheSimulator::CacheSimulator *cacheSimulator = new CacheSimulator::CacheSimulator(&cache, &memory);

        displaySimulator(memory, cacheSimulator);
    } else {
        printHelp();
        return 0;
    }
    return 0;
}

void displaySimulator(CacheSimulator::Memory &memory, CacheSimulator::CacheSimulator *cacheSimulator) {
    for (std::string line; getline(std::cin, line);) {
        memory.readLine(line);

        uint32_t address, data;
        std::string loading;
        std::istringstream string_stream(line);

        string_stream >> loading >> std::hex >> address >> std::dec >> data;

        if (loading == "l") {
            cacheSimulator->read(address);
        } else if (loading == "s") {
            cacheSimulator->write(address, data);
        }
    }
    cacheSimulator->display();
}

CacheSimulator::CacheConfig getConfig(char *const *argv) {
    uint32_t num_sets = strtoul(argv[1], NULL, 10);
    uint32_t num_blocks = strtoul(argv[2], NULL, 10);
    uint32_t num_bytes = strtoul(argv[3], NULL, 10);

    CacheSimulator::Allocation allocate = strcmp(argv[4], "write-allocate") ?
                                          CacheSimulator::WRITE_ALLOCATE : CacheSimulator::NO_WRITE_ALLOCATE;
    CacheSimulator::Write write = strcmp(argv[5], "write-back") ?
                                  CacheSimulator::WRITE_BACK : CacheSimulator::WRITE_THROUGH;
    CacheSimulator::CacheEviction eviction = strcmp(argv[6], "lru") ?
                                             CacheSimulator::LRU : CacheSimulator::FIFO;

    CacheSimulator::CacheConfig cacheConfig = CacheSimulator::CacheConfig(16777216, num_sets, num_blocks, num_bytes,
                                                                          allocate,
                                                                          write,
                                                                          eviction);
    return cacheConfig;
}

void printHelp() {
    std::cout << "No argument passed to program\n";
    std::cout << "Usage: " << "./csim <number-of-sets>"
              << " <number-of-blocks>"
              << " <number-of-bytes>"
              << " <allocation>"
              << " <write>"
              << " <cache-eviction>"
              << " < <filename>\n";
}
