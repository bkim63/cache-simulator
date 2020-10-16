/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 * 2. Rebecca Shao
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
