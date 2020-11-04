#pragma once

#include "global.h"

#include <vector>
#include <memory>
#include <array>
#include <stdint.h>

class Chunk
{
public:
    // Create Empty chunk
    Chunk();

    // Create Flatland chunk
    Chunk(uint64_t block, int height);

    // TODO: Custom Chunk Generator Support

private:
    // TODO: Configurable Chunk size
    // TODO: More Memory Efficient
    std::array<uint64_t, 16 * 16 * 255> blocks;
};