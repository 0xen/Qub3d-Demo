#pragma once

#include <qub3d/q3camera.hpp>

class Q3Renderer
{
  public:
    Q3Renderer();

    void clear();
    void drawCube(float x, float y, float z, float sx, float sy, float sz, glm::vec3 topCol);

    void handleCamera(Q3Camera *camera);

  private:
};