#include "chunk.h"

#include <algorithm>

Chunk::Chunk(u16 block, u16 height)
{
    std::fill_n(blocks, 16 * 16 * height, block);
}
