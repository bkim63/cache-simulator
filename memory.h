/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * Steven (Bumjin) Kim
 * bkim63@jhu.edu
 */
#ifndef MEMORY_H
#define MEMORY_H

#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "counter.h"

using std::make_pair;
using std::uint32_t;
using std::vector;

namespace bkim63 {
    class Memory {
    public:
        void readLine(const std::string &line);

        vector<uint32_t> readBlock(uint32_t address, uint32_t block_size);

        void writeBlock(uint32_t address, vector<uint32_t> data);

        void writeWord(uint32_t address, uint32_t data);

        uint32_t getReads() const;

        uint32_t getWrites() const;

    private:
        std::map<uint32_t, uint32_t> _data;

        mutable vector<uint32_t> _reads;
        mutable vector<std::pair<uint32_t, uint32_t> > _writes;
        mutable Counter _num_writes;
    };
}

#endif
