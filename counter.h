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

/*
 * Counter class for the increment operator
 */
namespace CacheSimulator {
    class Counter {
    public:
        /* 
        * Function for increment operator ++ 
        * 
        * Returns:
        *  Counter instance of ++
        */
        Counter &operator++();

        /* 
        * Function for increment operator ++ taken in int parameter
        * 
        * Parameters:
        *  int value
        * 
        * Returns:
        *  Counter instance of ++
        */
        Counter operator++(int);

        /* 
        * Getter for count field of counter
        * 
        * Returns:
        *  uint32_t _count field of counter
        */
        uint32_t getCount() const;

    private:
        uint32_t _count;

        /* 
        * Function to increment count field in Counter
        */
        void _increment();
    };
}

#endif
