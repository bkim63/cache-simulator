/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * Steven (Bumjin) Kim
 * bkim63@jhu.edu
 */
#include <sstream>
#include <iostream>
#include "memory.h"
#include "utils.h"

using namespace std;

namespace bkim63 {
    vector<uint32_t> Memory::readBlock(uint32_t address, uint32_t block_size) {
        uint32_t block_offset_bits = log2(block_size);

        // address must be the starting address of a block of size block_size
        assert(address == ((address >> block_offset_bits) << block_offset_bits));

        vector<uint32_t> block;
        for (uint32_t i = 0; i < block_size; ++i) {
            block.push_back(_data[address | i]);
        }

        _reads.push_back(address);

        return block;
    }

    void Memory::readLine(const std::string &line) {
        if (!line.empty()) {
            istringstream data_stream(line);
            if (!data_stream) {
                throw invalid_argument("Empty content from trace file");
            }

            uint32_t address, data;
            string loading;

            istringstream string_stream(line);

            string_stream >> loading >> hex >> address >> dec >> data;

            _data.insert(make_pair(address, data));
        }
    }

    uint32_t Memory::getReads() const {
        return _reads.size();
    }

    uint32_t Memory::getWrites() const {
        return _num_writes.getCount();
    }

    void Memory::writeBlock(uint32_t address, vector<uint32_t> data) {
        uint32_t block_size = data.size();

        assert(isPowerOf2(block_size));

        uint32_t block_offset_bits = log2(block_size);

        // address must be the starting address of a block of size block_size
        assert(address == ((address >> block_offset_bits) << block_offset_bits));

        for (uint32_t i = 0; i < block_size; ++i) {
            _data[address | i] = data[i];
            _writes.push_back(make_pair((address | i), data[i]));
        }

        ++_num_writes;
    }

    void Memory::writeWord(uint32_t address, uint32_t data) {
        _data[address] = data;
        _writes.push_back(make_pair(address, data));

        ++_num_writes;
    }
}
