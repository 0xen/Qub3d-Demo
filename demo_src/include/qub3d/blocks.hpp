#pragma once // Only be included once.

#include <glm/glm.hpp>
#include <string>

// The type of Qube, the "property" of the block.
namespace blocks
{
    enum class QubeType
    {
        Solid, // Solid Blocks, normal stuff like grass, stone all that jazz.
        Microblock, // Microblocks, one by one, instead of 2 by 2.
        Air, // Air, empty "blocks"
        Liquid, // Flowing stuff, probably unused for now.
        Collapsing // Collapsing blocks "fall" down, when blocks underneath it are removed
    };

    struct QubeData 
    {
        glm::vec3 position; // Position variable
        std::string blockName; // name of the block
        QubeType blockType = QubeType::Air; // Default block type is air
        std::string textureName; // name of the texture file. and append "side", "top" & "bottom" in code
    };
};