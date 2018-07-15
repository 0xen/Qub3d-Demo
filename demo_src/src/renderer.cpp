#include <qub3d/renderer.hpp>
#include <qub3d/opengl.hpp>

void GL11Renderer::renderMesh(Mesh *mesh)
{
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < mesh->indices.size(); i++) 
    {
        const unsigned int& index = mesh->indices[i];
        const glm::vec3& pos = mesh->vertices[index];

        glVertex3f(pos.x, pos.y, pos.z);
    }
    glEnd();
}