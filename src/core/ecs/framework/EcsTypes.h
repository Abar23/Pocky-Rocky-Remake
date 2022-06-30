#pragma once

#include <cstdint>
#include <bitset>

const std::uint32_t MAX_ENTITIES = 100;
const std::uint8_t MAX_COMPONENTS = 16;

using Entity = std::uint32_t;
using ComponentType = std::uint8_t;
using Signature = std::bitset<MAX_COMPONENTS>;