#include <qub3d/q3renderer.hpp>
#include <qub3d/q3opengl.hpp>

#include <qub3d/q3shared_constants.hpp>
#include <qub3d/q3texture.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Q3Texture *s_grass_texture;
Q3Texture *s_dirt_and_grass_texture;
Q3Texture *s_crosshair_texture;
Q3Texture *s_dirt_texture;
Q3Spritesheet *s_blocks;

glm::mat4 s_projection;

Q3Renderer::Q3Renderer()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    glEnable(GL_TEXTURE_2D);
    
    s_grass_texture = new Q3Texture("assets/grass.png");
    s_dirt_and_grass_texture = new Q3Texture("assets/sideGrass.png");
    s_crosshair_texture = new Q3Texture("assets/crosshair.png");
    s_dirt_texture = new Q3Texture("assets/dirt.png");

    s_blocks = new Q3Spritesheet("assets/blocks.png");

    Q3GameConfig *constants = Q3GameConfig::Get();
    glViewport(0, 0, constants->WindowWidth, constants->WindowHeight);

    s_projection = glm::perspective(Q3_FOV, (float)constants->WindowWidth / constants->WindowHeight, 0.1f, 100.0f);
}

void Q3Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Q3Renderer::handleCamera(Q3Camera *camera)
{
    glPushMatrix();
    camera->glLook();
}

void Q3Renderer::start3d()
{
    glMatrixMode(GL_PROJECTION);
    glm::mat4 perspective = s_projection;
    glLoadMatrixf(&perspective[0][0]);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void Q3Renderer::end3d()
{
    glPopMatrix();
    glPopMatrix();
}

void Q3Renderer::start2d()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.f, 1.f, -1.f, 1.f, -0.1f, 100.0f);
    glPushMatrix();
}

void Q3Renderer::end2d()
{
    glPopMatrix();
}

void Q3Renderer::drawRect(float x, float y, float w, float h, glm::vec3 col)
{
    glColor3f(col.r, col.g, col.b);
    glBegin(GL_QUADS);
    glVertex3f(x, y, 0.f);
    glVertex3f(x, y+h, 0.f);
    glVertex3f(x+w, y+h, 0.f);
    glVertex3f(x+w, y, 0.f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();
}

void Q3Renderer::drawCrosshair()
{
    glPushMatrix();
    glTranslatef(-0.1f, -0.1f, 0.1f);
    s_crosshair_texture->bind();
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.f, 1.f);
        glVertex2f(0.f, 0.f);

        glTexCoord2f(0.f, 0.f);
        glVertex2f(0.f, 0.2f);

        glTexCoord2f(1.f, 0.f);
        glVertex2f(0.2f, 0.2f);

        glTexCoord2f(1.f, 1.f);
        glVertex2f(0.2f, 0.f);
    }
    glEnd();
    s_crosshair_texture->unbind();

    glPopMatrix();
}

void Q3Renderer::drawCube(float x, float y, float z, float sx, float sy, float sz, Q3BlockRendereringData& data)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    s_blocks->bind();
    
    Q3Spritesheet::UVData top_uvs = s_blocks->getSprite(data.top_face.y, data.top_face.x);
    glBegin(GL_QUADS);
    {
        // top
        glTexCoord2f(top_uvs.BottomLeft.x, top_uvs.BottomLeft.y);
        glVertex3f(sx, sy, -sz);
        glTexCoord2f(top_uvs.TopLeft.x, top_uvs.TopLeft.y);
        glVertex3f(-sx, sy, -sz);
        glTexCoord2f(top_uvs.TopRight.x, top_uvs.TopRight.y);
        glVertex3f(-sx, sy, sz);
        glTexCoord2f(top_uvs.BottomRight.x, top_uvs.BottomRight.y);
        glVertex3f(sx, sy, sz);
    }
    glEnd();

    Q3Spritesheet::UVData bottom_uvs = s_blocks->getSprite(data.bottom_face.y, data.bottom_face.x);

    glBegin(GL_QUADS);
    {
        // bottom
        glTexCoord2f(bottom_uvs.BottomLeft.x, bottom_uvs.BottomLeft.y);
        glVertex3f(sx, -sy, sz);
        glTexCoord2f(bottom_uvs.TopLeft.x, bottom_uvs.TopLeft.y);
        glVertex3f(-sx, -sy, sz);
        glTexCoord2f(bottom_uvs.TopRight.x, bottom_uvs.TopRight.y);
        glVertex3f(-sx, -sy, -sz);
        glTexCoord2f(bottom_uvs.BottomRight.x, bottom_uvs.BottomRight.y);
        glVertex3f(sx, -sy, -sz);
    }
    glEnd();
    
    glBegin(GL_QUADS); 
    {
        Q3Spritesheet::UVData front_uvs = s_blocks->getSprite(data.forward_face.y, data.forward_face.x);
        // front
        glTexCoord2f(front_uvs.TopRight.x, front_uvs.TopRight.y);
        glVertex3f(sx, sy, sz);
        glTexCoord2f(front_uvs.TopLeft.x, front_uvs.TopLeft.y);
        glVertex3f(-sx, sy, sz);
        glTexCoord2f(front_uvs.BottomLeft.x, front_uvs.BottomLeft.y);
        glVertex3f(-sx, -sy, sz);
        glTexCoord2f(front_uvs.BottomRight.x, front_uvs.BottomRight.y);
        glVertex3f(sx, -sy, sz);

        Q3Spritesheet::UVData back_uvs = s_blocks->getSprite(data.backward_face.y, data.backward_face.x);

        // back
        glTexCoord2f(back_uvs.BottomRight.x, back_uvs.BottomRight.y);
        glVertex3f(sx, -sy, -sz);
        glTexCoord2f(back_uvs.BottomLeft.x, back_uvs.BottomLeft.y);
        glVertex3f(-sx, -sy, -sz);
        glTexCoord2f(back_uvs.TopLeft.x, back_uvs.TopLeft.y);
        glVertex3f(-sx, sy, -sz);
        glTexCoord2f(back_uvs.TopRight.x, back_uvs.TopRight.y);
        glVertex3f(sx, sy, -sz);

        Q3Spritesheet::UVData left_uvs = s_blocks->getSprite(data.left_face.y, data.left_face.x);

        // left
        glTexCoord2f(left_uvs.TopRight.x, left_uvs.TopRight.y);
        glVertex3f(-sx, sy, sz);
        glTexCoord2f(left_uvs.TopLeft.x, left_uvs.TopLeft.y);
        glVertex3f(-sx, sy, -sz);
        glTexCoord2f(left_uvs.BottomLeft.x, left_uvs.BottomLeft.y);
        glVertex3f(-sx, -sy, -sz);
        glTexCoord2f(left_uvs.BottomRight.x, left_uvs.BottomRight.y);
        glVertex3f(-sx, -sy, sz);

        Q3Spritesheet::UVData rights_uvs = s_blocks->getSprite(data.right_face.y, data.right_face.x);

        // right
        glTexCoord2f(rights_uvs.TopLeft.x, rights_uvs.TopLeft.y);
        glVertex3f(sx, sy, -sz);
        glTexCoord2f(rights_uvs.TopRight.x, rights_uvs.TopRight.y);
        glVertex3f(sx, sy, sz);
        glTexCoord2f(rights_uvs.BottomRight.x, rights_uvs.BottomRight.y);
        glVertex3f(sx, -sy, sz);
        glTexCoord2f(rights_uvs.BottomLeft.x, rights_uvs.BottomLeft.y);
        glVertex3f(sx, -sy, -sz);
    } 
    
    glEnd();
    s_blocks->unbind();
    glPopMatrix();
}