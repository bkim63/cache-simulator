/**
 * CSF Fall 2020
 * Cache implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 * 2. Rebecca Shao
 */

#include "counter.h"

namespace bkim63 {
    Counter &bkim63::Counter::operator++() {
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
