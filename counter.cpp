/**
 * CSF Fall 2020
 * Cache counter implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#include "counter.h"

namespace CacheSimulator {
    Counter &CacheSimulator::Counter::operator++() {
        _increment();
        return *this;
    }

    Counter Counter::operator++(int) {
        Counter temp(*this);
        _increment();
        return temp;
    }

    uint32_t Counter::getCount() const {
        return _count;
    }

    void Counter::_increment() {
        ++_count;
    }
}
