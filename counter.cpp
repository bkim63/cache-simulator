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
    /* 
     * Function for increment operator ++ 
     * 
     * Returns:
     *  Counter instance of ++
     */
    Counter &CacheSimulator::Counter::operator++() {
        _increment();
        return *this;
    }

     /* 
     * Function for increment operator ++ taken in int parameter
     * 
     * Parameters:
     *  int value
     * 
     * Returns:
     *  Counter instance of ++
     */
    Counter Counter::operator++(int) {
        Counter temp(*this);
        _increment();
        return temp;
    }

     /* 
     * Getter for count field of counter
     * 
     * Returns:
     *  uint32_t _count field of counter
     */
    uint32_t Counter::getCount() const {
        return _count;
    }

    /* 
     * Function to increment count field in Counter
     */
    void Counter::_increment() {
        ++_count;
    }
}
