#include <qub3d/q3world.hpp>

#include <qub3d/q3perlin.hpp>
#include <iostream>
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

bool s_wasClicked = false;
void Q3World::tick(Q3Camera * camera, Q3Window * window)
{
    glm::vec3 pos = camera->getPosition() + camera->getDirection();
    
    int mouse_x, mouse_y;
    Uint32 mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
    
    if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if (!s_wasClicked) {
            const float INC = 0.5f;
            
            float len = 0.f;
            Q3Block *hit = nullptr;

            while (len < 32.f && !hit) {
                pos += camera->getDirection() * INC;

                for (int i = 0; i < Q3_MAPSIZE * Q3_MAPSIZE; ++i) {
                    Q3Block *block = &(m_blocks[i]);
                    glm::vec3 bpos = block->position;

                    if (!block->exists)
                        continue;

                    if (pos.x > bpos.x - 1.f && pos.x < bpos.x + 1.f) {
                        if (pos.y > bpos.y - 1.f && pos.y < bpos.y + 1.f) {
                            if (pos.z > bpos.z - 1.f && pos.z < bpos.z + 1.f) {
                                hit = block;
                                break;
                            }
                        }
                    }
                }

                if (hit) {
                    hit->exists = false;
                }
                
                len += INC;
            }

            s_wasClicked = true;
        }
    }
    else {
        s_wasClicked = false;
    }
}

void Q3WorldRenderer::render(Q3World * world, Q3Renderer *renderer)
{
    Q3Block *blocks = world->getBlocks();
    for (int i = 0; i < Q3_MAPSIZE * Q3_MAPSIZE; ++i)
    {
        Q3Block *block = &(blocks[i]);
        const glm::vec3& block_pos = block->position;
        if(block->exists)
            renderer->drawCube(block_pos.x, block_pos.y, block_pos.z, 1, 1, 1);
    }
}
