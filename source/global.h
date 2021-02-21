#pragma once

#include <vector>

#include "util/types.h"

// Key:   Block ID
// Value: Module Handle
static std::vector<u32> blockMap;

// Key:   Module Handle
// Value: Offset to internal Block ID
static std::vector<u16> moduleOffsets;

// Converts BlockID/Module Handle pair into internal_blockID for internal Module use
static inline const u32 internal_blockID(u16 moduleHandle, u32 blockID)
{
    return blockID - moduleOffsets.at(moduleHandle);
}
