#pragma once

#include <qub3d/q3camera.hpp>
#include <qub3d/q3block.hpp>

class Q3Renderer
{
  public:
    Q3Renderer();

    void clear();
    void drawCube(float x, float y, float z, float sx, float sy, float sz, Q3BlockRendereringData& data);

    void handleCamera(Q3Camera *camera);

    void start3d();
    void end3d();

    void start2d();
    void end2d();

    void drawRect(float x, float y, float w, float h, glm::vec3 col);
    
    void drawCrosshair();

  private:
};