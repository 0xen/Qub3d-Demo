#include <qub3d/q3renderer.hpp>
#include <qub3d/q3opengl.hpp>

#include <qub3d/q3shared_constants.hpp>

#include <glm/gtc/matrix_transform.hpp>

Q3Renderer::Q3Renderer() {
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
}

void Q3Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Q3Renderer::handleCamera(Q3Camera *camera) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera->glLook();
}

void Q3Renderer::drawCube(float x, float y, float z, float sx, float sy, float sz, glm::vec3 topCol) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    {
        // top
        glColor3f(topCol.x, topCol.y,topCol.z);
        glVertex3f(sx, sy, -sz);
        glVertex3f(-sx, sy, -sz);
        glVertex3f(-sx, sy, sz);
        glVertex3f(sx, sy, sz);

        // bottom
        glColor3f(89.f/255.f,87.f/ 255.f,87.f/255.f);
        glVertex3f(sx, -sy, sz);
        glVertex3f(-sx, -sy, sz);
        glVertex3f(-sx, -sy, -sz);
        glVertex3f(sx, -sy, -sz);

        // front
        //glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(sx, sy, sz);
        glVertex3f(-sx, sy, sz);
        glVertex3f(-sx, -sy, sz);
        glVertex3f(sx, -sy, sz);

        // back
        //glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(sx, -sy, -sz);
        glVertex3f(-sx, -sy, -sz);
        glVertex3f(-sx, sy, -sz);
        glVertex3f(sx, sy, -sz);

        // left
        //glColor3f(0.0f, 0.0f, 1.0f); 
        glVertex3f(-sx, sy, sz);
        glVertex3f(-sx, sy, -sz);
        glVertex3f(-sx, -sy, -sz);
        glVertex3f(-sx, -sy, sz);

        // right
        //glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(sx, sy, -sz);
        glVertex3f(sx, sy, sz);
        glVertex3f(sx, -sy, sz);
        glVertex3f(sx, -sy, -sz);
    }
    glEnd();
    glPopMatrix();
}