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

namespace CacheSimulator {
    class CacheBlock {
    public:
        CacheBlock() {
            _isEmpty = false;
            _dirty = false;
            _time = 0;
            _tag = "";
        }

        CacheBlock(std::string tag) {
            _dirty = false;
            _isEmpty = false;
            _time = 0;
            _tag = tag;
        }

        CacheBlock(std::string tag, bool dirt) {
            _isEmpty = false;
            _dirty = dirt;
            _time = 0;
            _tag = tag;
        }

        CacheBlock(int i, bool isEmpty) {
            _time = 0;
            _tag = "";
            _isEmpty = isEmpty;
            _placeholder = i;
            _dirty = false;
        }

        void setDirty();

        void clearDirty();

        void countTime();

        void resetTime();

        void updateTag(std::string tag);

        int getTime() {
            return _time;
        }

        std::string getTag() {
            return _tag;
        }

        bool getDirty() {
            return _dirty;
        }

        bool isEmpty() {
            return _isEmpty;
        }

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
