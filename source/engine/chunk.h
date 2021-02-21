#pragma once

#include "global.h"
#include "util/types.h"

class Chunk
{
public:
    // Create Chunk
    Chunk(u16 block = 0, u16 height = 255);

    // TODO: Custom Chunk Generator Support

private:
    // TODO: Configurable Chunk size
    // TODO: More Memory Efficient
    u16 blocks[16 * 16 * 255];    // <array> aparrently has very bad compile times
};