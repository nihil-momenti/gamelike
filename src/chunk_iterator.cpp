#include "chunk_iterator.hpp"

#include "debug.hpp"

ChunkIterator::ChunkIterator(Chunk *chunk)
    : chunk(chunk), i(0), j(0), k(0), y(0), n(0), side(0), l(0) {
}

ChunkIterator::ChunkIterator(Chunk *chunk, int throwaway)
    : chunk(chunk), i(0), j(0), k(0), y(CHUNK_HEIGHT), n(0), side(0), l(0) {
}

bool ChunkIterator::operator== (const ChunkIterator &other) {
    return (
        (i == other.i) &&
        (j == other.j) &&
        (k == other.k) &&
        (y == other.y)
   );
}

bool ChunkIterator::operator!= (const ChunkIterator &other) {
    return !((*this) == other);
}

ChunkIterator & ChunkIterator::operator++ () {
    return this->operator++(0);
}

ChunkIterator & ChunkIterator::operator++ (int val) {
    if (y == CHUNK_HEIGHT) {
        return (*this);
    } else if (n == 0) {
        n += 1;
        i = n;
        l = n;
    } else {
        if (l == 0) {
            side++;
            l = n;
        }
        l -= 1;
        switch(side) {
            case 0:
                i -= 1;
                j += 1;
                break;
            case 1:
                j -= 1;
                k += 1;
                break;
            case 2:
                k -= 1;
                i -= 1;
                break;
            case 3:
                i += 1;
                j -= 1;
                break;
            case 4:
                j += 1;
                k -= 1;
                break;
            case 5:
                if (l == 0) {
                    side = 0;
                    i = j = k = 0;
                    if (n == CHUNK_SIZE) {
                        y += 1;
                        n = 0;
                    } else {
                        n += 1;
                        i = n;
                        l = n;
                    }
                } else {
                    k += 1;
                    i += 1;
                }
                break;
        }
    }

    return (*this);
}

int ChunkIterator::index(int i, int j, int k, int y) {
    i = i - k + CHUNK_SIZE;
    j = j + k + CHUNK_SIZE;

    int index_in_level = (i + j + 1) * (i + j) / 2 - (CHUNK_SIZE + 1) * CHUNK_SIZE / 2 + j;
    int level_index = (3 * CHUNK_SIZE * (CHUNK_SIZE + 1) + 1) * y;

    return level_index + index_in_level;
}

BlockWrapper ChunkIterator::operator* () {
    return BlockWrapper(chunk->blocks[index(i,j,k,y)], i, j, k, y, index(i, j, k, y));
}
