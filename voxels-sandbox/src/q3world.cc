#include <qub3d/q3world.hpp>
#include <qub3d/q3generator.hpp>

#include <iostream>
#include <vector>
#include <functional>

Q3BlockRendereringData Q3World::blocks[Q3_NO_BLOCKS] = {
    Q3BlockRendereringData({1, 0}, {0,0},{2,0}, {2,0},{ 2,0 },{ 2,0 }),
    Q3BlockRendereringData({ 0, 0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 })
};

void Q3World::generate()
{
    // Lets fill the world out with empty air blocks before generating any terrain.
    for (int y = 0; y < Q3_MAPSIZE; ++y) 
    {
        for (int z = 0; z < Q3_MAPSIZE; ++z) 
        {
            for (int x = 0; x < Q3_MAPSIZE; ++x) 
            {
                Q3Block *block = &(m_blocks[x][y][z]);
                block->position.x = x * 2;
                block->position.y = y * 2;
                block->position.z = z * 2;
            }
        }
    }
    
    /*
     Now lets actually generate the terrain blocks.
     Only places the top layer for now.
    */
    Q3PerlinNoiseGenerator perlin;
    for (int z = 0; z < Q3_MAPSIZE; ++z) 
    {
        for (int x = 0; x < Q3_MAPSIZE; ++x) 
        {
            // Don't ask how this works. Please.
            float normalized_perlin = perlin.perlin(glm::vec3((x * 2.f) / 10.f, (z * 2.f) / 10.f, 0.f));
            float scaled_perlin = normalized_perlin * 15.f;
            float rounded_scaled_perlin = static_cast<float>((int)(scaled_perlin / 2) * 2);

            int y_index = rounded_scaled_perlin / 2;
            Q3Block *block = &(m_blocks[x][y_index][z]);
            for (int i = 0; i < y_index; i++) {
                (m_blocks[x][i][z]).type = Q3BlockType::Dirt;
            }
            block->position.y = rounded_scaled_perlin;
            block->type = Q3BlockType::Grass;
            block->position.x = std::round(+(x * 2.f));
            block->position.z = std::round(+(z * 2.f));
        }
    }
}

// These are used to keep track of is the left and right mouse buttons are being held down or not.
// Useful when we only need to do an action when a button is first placed
bool s_right_button_was_clicked = false;
bool s_left_button_was_clicked = false;

void doOnce(bool condition, bool& flag, std::function<void()> action) 
{
    if (condition) 
    {
        if (!flag) 
        {
            action();
            flag = true;
        }
    }
    else 
    {
        flag = false;
    }
}

void Q3World::tick(Q3Camera * camera, Q3Window * window)
{
    glm::vec3 pos = camera->getPosition() + camera->getDirection();
    
    Uint32 mouse_state = SDL_GetMouseState(NULL, NULL);
    
    const float RAY_INCREMENT = 0.5f;
    const float PICKING_RANGE = 32.f;

    // Only do this when Q3_MOUSE_BUTTON_PLACE_BLOCK is first pressed
    doOnce(mouse_state & SDL_BUTTON(Q3_MOUSE_BUTTON_PLACE_BLOCK), s_left_button_was_clicked,
        [&]()
        {
            float ray_length = 0.f;

            while (ray_length < PICKING_RANGE) 
            {
                // Advance the ray in the direction that the camera is facing.
                pos += camera->getDirection() * RAY_INCREMENT;

                /*
                    If we hit a non air block, move to the last position of the ray before entering that block
                    then place a block at that position.
                */
                Q3Block *hit = getBlockAtPos(pos, true);
                if (hit != nullptr) 
                {
                    pos -= camera->getDirection() * RAY_INCREMENT;
                    hit = getBlockAtPos(pos, false);

                    if (hit != nullptr) 
                    {
                        hit->type = Q3BlockType::Dirt;
                        break;
                    }
                }

                ray_length += RAY_INCREMENT;
            }
        }
    );

    // Only do this when Q3_MOUSE_BUTTON_DESTROY_BLOCK is first pressed
    doOnce(mouse_state & SDL_BUTTON(Q3_MOUSE_BUTTON_DESTROY_BLOCK), s_right_button_was_clicked,
        [&]() 
        { 
            float ray_length = 0.f;

            while (ray_length < PICKING_RANGE) 
            {
                // Advance the ray in the direction the camera is facing.
                pos += camera->getDirection() * RAY_INCREMENT;

                /*
                    Get any non-air block at the current position of the ray and if
                    there is one, destroy it (by making it an air block)
                */
                Q3Block *hit = getBlockAtPos(pos, true);
                if (hit != nullptr) 
                {
                    hit->type = Q3BlockType::Air;
                    break;
                }

                ray_length += RAY_INCREMENT;
            }
        }
    );
}

Q3Block * Q3World::getBlockAtPos(glm::vec3 pos, bool ignoreAir)
{
    for (int x = 0; x < Q3_MAPSIZE; ++x) 
    {
        for (int y = 0; y < Q3_MAPSIZE; ++y) 
        {
            for (int z = 0; z < Q3_MAPSIZE; ++z) 
            {
                Q3Block *block = &(m_blocks[x][y][z]);

                if (ignoreAir && block->type == Q3BlockType::Air) 
                {
                    continue;
                }

                glm::vec3 block_pos = block->position;
                
                // Simple AABB collision check.
                bool point_is_inside_aabb = 
                    pos.x > block_pos.x - 1.f && pos.x < block_pos.x + 1.f &&
                    pos.y > block_pos.y - 1.f && pos.y < block_pos.y + 1.f &&
                    pos.z > block_pos.z - 1.f && pos.z < block_pos.z + 1.f;

                if (point_is_inside_aabb) 
                {
                    return &(m_blocks[x][y][z]);
                }
            }
        }
    }

    /*
    There is no block at the current position
    or it is an air block and `ignoreAir` is set to true.
    */
    return nullptr;
}

void Q3WorldRenderer::render(Q3World * world, Q3Renderer *renderer)
{
    Q3World::Q3BlocksArray& blocks = world->getBlocks();

    for (int x = 0; x < Q3_MAPSIZE; x++) 
    {
        for (int y = 0; y < Q3_MAPSIZE; y++) 
        {
            for (int z = 0; z < Q3_MAPSIZE; z++) 
            {
                Q3Block *block = &(blocks[x][y][z]);
                const glm::vec3& block_pos = block->position;

                // We don't see air blocks therefore don't render them,
                // (despite them still existing as block data)
                if (block->type != Q3BlockType::Air) 
                {
                    Q3BlockRendereringData& data = Q3World::blocks[(int)block->type];
                    renderer->drawCube(block_pos.x, block_pos.y, block_pos.z, 1, 1, 1, data);
                }
            }
        }
    }
}
