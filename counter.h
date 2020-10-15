/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * Steven (Bumjin) Kim
 * bkim63@jhu.edu
 */
#ifndef COUNTER_H
#define COUNTER_H

#include <cstdint>

namespace bkim63 {
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
