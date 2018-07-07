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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glm::mat4 perspective = glm::perspective(Q3_FOV, (float)Q3_WINDOWWIDTH / Q3_WINDOWHEIGHT, 0.1f, 100.0f);
    glLoadMatrixf(&perspective[0][0]);

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
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera->glLook();
}

void Q3Renderer::drawCube(float x, float y, float z, float sx, float sy, float sz, glm::vec3 topCol)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    grassTexture->bind();
    glBegin(GL_QUADS);
    {
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        // top
        //glColor3f(topCol.x, topCol.y, topCol.z);
        glTexCoord2f(0, 0);
        glVertex3f(sx, sy, -sz);
        glTexCoord2f(0, 1);
        glVertex3f(-sx, sy, -sz);
        glTexCoord2f(1, 1);
        glVertex3f(-sx, sy, sz);
        glTexCoord2f(1, 0);
        glVertex3f(sx, sy, sz);

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
        // bottom
        //glColor3f(89.f / 255.f, 87.f / 255.f, 87.f / 255.f);
        

        // front
        //glColor3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(1, 0); 
        glVertex3f(sx, sy, sz);
        glTexCoord2f(0, 0);
        glVertex3f(-sx, sy, sz);
        glTexCoord2f(0, 1);
        glVertex3f(-sx, -sy, sz);
        glTexCoord2f(1, 1);
        glVertex3f(sx, -sy, sz);

        // back
        //glColor3f(1.0f, 1.0f, 0.0f);
        glTexCoord2f(1, 1);
        glVertex3f(sx, -sy, -sz);
        glTexCoord2f(0, 1);
        glVertex3f(-sx, -sy, -sz);
        glTexCoord2f(0, 0);
        glVertex3f(-sx, sy, -sz);
        glTexCoord2f(1, 0);
        glVertex3f(sx, sy, -sz);

        // left
        //glColor3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(1, 0);
        glVertex3f(-sx, sy, sz);
        glTexCoord2f(0,0);
        glVertex3f(-sx, sy, -sz);
        glTexCoord2f(0, 1);
        glVertex3f(-sx, -sy, -sz);
        glTexCoord2f(1, 1);
        glVertex3f(-sx, -sy, sz);

        // right
        //glColor3f(1.0f, 0.0f, 1.0f);
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