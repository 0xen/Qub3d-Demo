#include <qub3d/q3world.hpp>

#include <qub3d/q3perlin.hpp>

void Q3World::generate()
{
    memset(m_blocks, 0, Q3_MAPSIZE * Q3_MAPSIZE);
    Q3PerlinNoiseGenerator perlin;
    for (int z = 0; z < Q3_MAPSIZE; ++z) {
        for (int x = 0; x < Q3_MAPSIZE; ++x) {
            Q3Block *block = &(m_blocks[x + z * Q3_MAPSIZE]);
            block->position.x = std::round(+(x * 2.f));
            block->position.z = std::round(+(z * 2.f));

            float normalized_perlin = perlin.perlin(glm::vec3((x * 2.f) / 10.f, (z * 2.f) / 10.f, 0.f));
            float scaled_perlin = normalized_perlin * 15.f;
            float rounded_scaled_perlin = static_cast<float>((int)(scaled_perlin / 2) * 2);

            block->position.y = rounded_scaled_perlin;
        }
    }
}

void Q3WorldRenderer::render(Q3World * world, Q3Renderer *renderer)
{
    Q3Block *blocks = world->getBlocks();
    for (int i = 0; i < Q3_MAPSIZE * Q3_MAPSIZE; ++i)
    {
        Q3Block *block = &(blocks[i]);
        const glm::vec3& block_pos = block->position;

        renderer->drawCube(block_pos.x, block_pos.y, block_pos.z, 1, 1, 1);
    }
}
