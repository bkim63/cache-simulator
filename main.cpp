/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 * 2. Rebecca Shao
 */

#include <sstream>
#include "cachesimulator.h"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

    if (argc == 7) {
        uint32_t num_sets = strtoul(argv[1], NULL, 10);
        uint32_t num_blocks = strtoul(argv[2], NULL, 10);
        uint32_t num_bytes = strtoul(argv[3], NULL, 10);

        bkim63::Allocation allocate = strcmp(argv[4], "write-allocate") ?
                                      bkim63::WRITE_ALLOCATE : bkim63::NO_WRITE_ALLOCATE;
        bkim63::Write write = strcmp(argv[5], "write-back") ?
                              bkim63::WRITE_BACK : bkim63::WRITE_THROUGH;
        bkim63::CacheEviction eviction = strcmp(argv[6], "lru") ?
                                         bkim63::LRU : bkim63::FIFO;

        bkim63::CacheConfig cacheConfig = bkim63::CacheConfig(16777216, num_sets, num_blocks, num_bytes, allocate,
                                                              write,
                                                              eviction);
        bkim63::Cache cache(cacheConfig);
        bkim63::Memory memory;

        bkim63::CacheSimulator *cacheSimulator = new bkim63::CacheSimulator(&cache, &memory);

        for (string line; getline(cin, line);) {
            memory.readLine(line);

            uint32_t address, data;
            string loading;

            istringstream string_stream(line);

            string_stream >> loading >> hex >> address >> dec >> data;

            if (loading == "l") {
                cacheSimulator->read(address);
            } else if (loading == "s") {
                cacheSimulator->write(address, data);
            }
        }

        cacheSimulator->display();

    } else {
        cout << "No argument passed to program\n";
        cout << "Usage: " << "./csim <number-of-sets>"
             << " <number-of-blocks>"
             << " <number-of-bytes>"
             << " <allocation>"
             << " <write>"
             << " <cache-eviction>"
             << " < <filename>\n";
        return 0;
    }


    return 0;
}
