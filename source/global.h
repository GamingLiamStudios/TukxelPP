#pragma once

#include "slot_map.h"
#include <stdint.h>

// TODO: Make this more memory efficent

// Key:   Block ID
// Value: Module Handle
static TSlotMap<int> blockMap;

// Key:   Module Handle
// Value: Offset to internal Block ID
static TSlotMap<uint64_t> moduleOffsets;

// Converts BlockID/Module Handle pair into internal_blockID for Modules
static inline const uint64_t internal_blockID(int moduleHandle, uint64_t blockID)
{
    return blockID - *moduleOffsets.at(moduleHandle);
}
