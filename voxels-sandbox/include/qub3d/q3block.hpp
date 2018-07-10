#pragma once

#include <glm/glm.hpp>

/*
The type of the block. A property of Q3Block
*/
enum class Q3BlockType
{
    Grass = 0, 
    Dirt = 1,
    Air = 2
};

/*
Stores data on how a block should be rendered,
for example the texture UVsfor front,back,top,left,right,bottom sides etc...
*/
struct Q3BlockRendereringData {
    glm::ivec2 top_face;
    glm::ivec2 bottom_face;

    glm::ivec2 left_face;
    glm::ivec2 right_face;

    glm::ivec2 forward_face;
    glm::ivec2 backward_face;

    Q3BlockRendereringData() {}
    
    Q3BlockRendereringData(
        const glm::ivec2& t, const glm::ivec2& bo,
        const glm::ivec2& l, const glm::ivec2& r,
        const glm::ivec2& f, const glm::ivec2& ba) : top_face(t), bottom_face(bo), left_face(l), right_face(r), forward_face(f), backward_face(ba) {}
};

/*
Stores data about each block, such as its position or type.
Each block is 2x2x2 in size.
*/
struct Q3Block
{
    glm::vec3 position;
    Q3BlockType type = Q3BlockType::Air;
};
