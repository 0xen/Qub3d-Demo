#pragma once

class Q3Texture {
public:
    Q3Texture(const char *filepath);
    
    void bind();
    void unbind();

    unsigned int getTextureId();

private:
    unsigned int m_glTexture;
};