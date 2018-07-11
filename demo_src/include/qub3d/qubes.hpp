#pragma once

#include <glm/glm.hpp>

// The type of Qube, the "property" of the block.
namespace qubes
{
    enum class QubeType
    {
        Solid, // Solid Blocks, normal stuff like grass, stone all that jazz.
        Microblock, // Microblocks, one by one, instead of 2 by 2.
        Air, // Air, empty "blocks"
        Liquid, // Flowing stuff, probably unused for now.
        Collapsing // Collapsing blocks "fall" down, when blocks underneath it are removed
    };
};