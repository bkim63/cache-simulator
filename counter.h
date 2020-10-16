/**
 * CSF Fall 2020
 * Cache counter function declarations
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#ifndef COUNTER_H
#define COUNTER_H

#include <cstdint>

namespace CacheSimulator {
    class Counter {
    public:
        Counter &operator++();
        Counter operator++(int);

        uint32_t getCount() const;

    private:
        uint32_t _count;

        void _increment();
    };
}

#endif
