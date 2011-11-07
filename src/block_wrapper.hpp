#pragma once

#include "block.hpp"

class BlockWrapper {
    public:
        Block &block;
        int i, j, k, y;

        BlockWrapper(Block &block, int i, int j, int k, int y)
            : block(block), i(i), j(j), k(k), y(y) { };
};
