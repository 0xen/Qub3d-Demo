#pragma once

#include <glm/glm.hpp>

#include <qub3d/q3shared_constants.hpp>
#include <qub3d/q3renderer.hpp>

#include <qub3d/q3camera.hpp>
#include <qub3d/q3window.hpp>
#include <qub3d/q3block.hpp>

#include <array>

/*
Represents the game world, storing block data and handling voxel manipulation.
Can be rendered via the Q3WorldRenderer class.
*/
class Q3World 
{
public:
    static Q3BlockRendereringData blocks[Q3_NO_BLOCKS];

    typedef std::array<std::array<std::array<Q3Block, Q3_MAPSIZE>, Q3_MAPSIZE>, Q3_MAPSIZE> Q3BlocksArray;

    /* Generate the worlds terrain. This includes air. Can be called multiple times to regenerate the world. */
    void generate();

    /* Update the world. Includes handling world editing such as placing/destroying blocks. */
    void tick(Q3Camera *camera, Q3Window *window);

    /* Get the 3D array structure containing the block data. */
    Q3BlocksArray& getBlocks() { return m_blocks; }

private:
    /* 
        Return the block at the specified position. 
        If ignoreAir = true then it will only return blocks that are not air.

        If there is no block at the specified position OR ignoreAir is true and it is an air block at that position, return NULL.
    */
    Q3Block * getBlockAtPos(glm::vec3 pos, bool ignoreAir);

private:

    Q3BlocksArray m_blocks;
};

class Q3WorldRenderer 
{
public:
    /* Draw the world to the current OpenGL context. */
    void render(Q3World *world, Q3Renderer *renderer);
};