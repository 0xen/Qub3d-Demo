#pragma once

#include <glm/glm.hpp>

class Q3Texture {
public:
    Q3Texture(const char *filepath);
    
    void bind();
    void unbind();

    unsigned int getTextureId();

private:
    unsigned int m_glTexture;
};

class Q3Spritesheet {
public:
    struct UVData {
        glm::vec2 BottomLeft, TopLeft;
        glm::vec2 BottomRight, TopRight;
    };

    Q3Spritesheet(const char *filepath);
    ~Q3Spritesheet();

    void bind() { m_texture->bind(); }
    void unbind() { m_texture->unbind(); }

    UVData getSprite(int spriteRow, int spriteColumn);

private:
    Q3Texture * m_texture;
};