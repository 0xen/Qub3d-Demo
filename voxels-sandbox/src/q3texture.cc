#include <qub3d/q3texture.hpp>
#include <qub3d/q3opengl.hpp>

#include <qub3d/q3shared_constants.hpp>

#include <lodepng/lodepng.h>

Q3Texture::Q3Texture(const char *filepath): m_glTexture(0)
{
    glGenTextures(1, &m_glTexture);
    bind();

    std::vector<unsigned char> pixels;
    unsigned int w, h;
    lodepng::decode(pixels, w, h, filepath);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    unsigned char *pData = pixels.data();
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        w, h,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        pData
    );
    unbind();
}

unsigned int Q3Texture::getTextureId() 
{
    return m_glTexture;
}

void Q3Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, m_glTexture);
}

void Q3Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Q3Spritesheet::Q3Spritesheet(const char * filepath)
{
    m_texture = new Q3Texture(filepath);
}

Q3Spritesheet::~Q3Spritesheet()
{
    delete m_texture;
}

Q3Spritesheet::UVData Q3Spritesheet::getSprite(int spriteRow, int spriteColumn)
{
    Q3Spritesheet::UVData uvs;

    int atlasW = 256;
    int atlasH = 256;

    float fx = spriteColumn * Q3_SPRITESIZE;
    float fy = spriteRow * Q3_SPRITESIZE;
    float w = Q3_SPRITESIZE;
    float h = Q3_SPRITESIZE;
    uvs.TopLeft = glm::vec2(fx / atlasW, fy / atlasH);
    uvs.TopRight = glm::vec2((fx + w) / atlasW, fy / atlasH);
    uvs.BottomLeft = glm::vec2(fx / atlasW, (fy + h) / atlasH);
    uvs.BottomRight = glm::vec2((fx + w) / atlasW, (fy + h) / atlasH);

    return uvs;
}
