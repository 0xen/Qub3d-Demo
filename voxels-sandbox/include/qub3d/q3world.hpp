#pragma once

#include <glm/glm.hpp>

#include <qub3d/q3shared_constants.hpp>
#include <qub3d/q3renderer.hpp>

struct Q3Block {
    glm::vec3 position;
};

class Q3World {
public:
    void generate();

    Q3Block *getBlocks() { return m_blocks; }
private:
    Q3Block m_blocks[Q3_MAPSIZE * Q3_MAPSIZE];
};

class Q3WorldRenderer {
public:
    void render(Q3World *world, Q3Renderer *renderer);
};