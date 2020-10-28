/**
 * CSF Fall 2020
 * CacheBlock implementation
 * Assignment 3
 * 1. Steven (Bumjin) Kim
 *    bkim63@jhu.edu
 * 2. Rebecca Shao
 *    rshao5@jhu.edu
 */

#ifndef CACHE_BLOCK_H
#define CACHE_BLOCK_H

#include <string>

/* 
 * CacheBlock class whose instance is a block in the cache.
 */
namespace CacheSimulator {
    class CacheBlock {
    public:
        /* 
        * Constructor of cache block with no parameters.
        */
        CacheBlock() {
            _isEmpty = false;
            _dirty = false;
            _time = 0;
            _tag = "";
        }

        /* 
        * Constructor of cache block with tag parameter.
        * 
        * Parameters:
        *  tag - string to set _tag field
        */
        CacheBlock(std::string tag) {
            _dirty = false;
            _isEmpty = false;
            _time = 0;
            _tag = tag;
        }

        /* 
        * Constructor of cache block with tag and dirt parameters.
        * 
        * Parameters:
        *  tag - string to set _tag field
        *  dirt - boolean to set _dirty field 
        */
        CacheBlock(std::string tag, bool dirt) {
            _isEmpty = false;
            _dirty = dirt;
            _time = 0;
            _tag = tag;
        }

        /* 
        * Constructor of cache block with two parameters.
        * 
        * Parameters:
        *  i - int to set _placeholder field
        *  isEmpty - boolean to set _isEmpty field
        */
        CacheBlock(int i, bool isEmpty) {
            _time = 0;
            _tag = "";
            _isEmpty = isEmpty;
            _placeholder = i;
            _dirty = false;
        }

        /* 
        * Make cache block dirty
        */
        void setDirty();

        /* 
        * Make cache block clean
        */
        void clearDirty();

        /* 
        * Increment time field of cache block
        */
        void countTime();

        /* 
        * Reset time field to 0
        */
        void resetTime();

        /* 
        * Setter for tag field
        * 
        * Parameters:
        *  tag - string to set _tag field to
        */
        void updateTag(std::string tag);

        /* 
        * Getter for time field
        * 
        * Returns:
        *  int _time field of cache block
        */
        int getTime() {
            return _time;
        }

        /* 
        * Getter for tag field
        * 
        * Returns:
        *  int _tag field of cache block
        */
        std::string getTag() {
            return _tag;
        }

        /* 
        * Getter for dirty field
        * 
        * Returns:
        *  int _dirty field of cache block
        */
        bool getDirty() {
            return _dirty;
        }

        /* 
        * Function to indicate if cache block is empty
        * 
        * Returns:
        *  boolean of if cache block is empty
        */
        bool isEmpty() {
            return _isEmpty;
        }

        /* 
        * Set cache block as empty
        */
        void setEmpty();

    private:
        std::string _tag;

        bool _dirty;
        int _time;

        bool _isEmpty;
        int _placeholder;
    };

}

#endif
