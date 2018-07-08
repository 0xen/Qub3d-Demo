#include <qub3d/q3renderer.hpp>
#include <qub3d/q3opengl.hpp>

#include <qub3d/q3shared_constants.hpp>
#include <qub3d/q3texture.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Q3Texture *grassTexture;
Q3Texture *sideTexture;

Q3Renderer::Q3Renderer()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);
    glViewport(0, 0, Q3_WINDOWWIDTH, Q3_WINDOWHEIGHT);
    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 perspective = glm::perspective(Q3_FOV, (float)Q3_WINDOWWIDTH / Q3_WINDOWHEIGHT, 0.1f, 100.0f);
    glLoadMatrixf(&perspective[0][0]);*/

    glEnable(GL_TEXTURE_2D);
    
    grassTexture = new Q3Texture("assets/grass.png");
    sideTexture = new Q3Texture("assets/sideGrass.png");
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
    glm::mat4 perspective = glm::perspective(Q3_FOV, (float)Q3_WINDOWWIDTH / Q3_WINDOWHEIGHT, 0.1f, 100.0f);
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
        glColor3ub(240, 240, 240); //white
        glLineWidth(2.0);
        
        glBegin(GL_LINES);

        glVertex3f(-0.05f, 0.f, 0.f);
        glVertex3f(0.05f, 0.f, 0.f);

        glEnd();

        glBegin(GL_LINES);

        glVertex3f(0.f, -0.05f, 0.f);
        glVertex3f(0.f, 0.05f, 0.f);

        glEnd();
}

void Q3Renderer::drawCube(float x, float y, float z, float sx, float sy, float sz)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    grassTexture->bind();
    glBegin(GL_QUADS);
    {
        // top
        glTexCoord2f(0, 0);
        glVertex3f(sx, sy, -sz);
        glTexCoord2f(0, 1);
        glVertex3f(-sx, sy, -sz);
        glTexCoord2f(1, 1);
        glVertex3f(-sx, sy, sz);
        glTexCoord2f(1, 0);
        glVertex3f(sx, sy, sz);
        
        // bottom
        glTexCoord2f(0, 0);
        glVertex3f(sx, -sy, sz);
        glTexCoord2f(0, 1);
        glVertex3f(-sx, -sy, sz);
        glTexCoord2f(1, 1);
        glVertex3f(-sx, -sy, -sz);
        glTexCoord2f(1, 0);
        glVertex3f(sx, -sy, -sz);
    }
    glEnd();
    grassTexture->unbind();
    
    sideTexture->bind();
    glBegin(GL_QUADS);
    {
        // front
        glTexCoord2f(1, 0); 
        glVertex3f(sx, sy, sz);
        glTexCoord2f(0, 0);
        glVertex3f(-sx, sy, sz);
        glTexCoord2f(0, 1);
        glVertex3f(-sx, -sy, sz);
        glTexCoord2f(1, 1);
        glVertex3f(sx, -sy, sz);

        // back
        glTexCoord2f(1, 1);
        glVertex3f(sx, -sy, -sz);
        glTexCoord2f(0, 1);
        glVertex3f(-sx, -sy, -sz);
        glTexCoord2f(0, 0);
        glVertex3f(-sx, sy, -sz);
        glTexCoord2f(1, 0);
        glVertex3f(sx, sy, -sz);

        // left
        glTexCoord2f(1, 0);
        glVertex3f(-sx, sy, sz);
        glTexCoord2f(0,0);
        glVertex3f(-sx, sy, -sz);
        glTexCoord2f(0, 1);
        glVertex3f(-sx, -sy, -sz);
        glTexCoord2f(1, 1);
        glVertex3f(-sx, -sy, sz);

        // right
        glTexCoord2f(0, 0);
        glVertex3f(sx, sy, -sz);
        glTexCoord2f(1, 0);
        glVertex3f(sx, sy, sz);
        glTexCoord2f(1, 1);
        glVertex3f(sx, -sy, sz);
        glTexCoord2f(0, 1);
        glVertex3f(sx, -sy, -sz);
    } 
    glEnd();
    sideTexture->unbind();
    glPopMatrix();
}