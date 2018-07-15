#pragma once

#include <glm/glm.hpp>
#include <qub3d/window.hpp>

namespace q3 
{
    class Camera 
    {
    public:
        glm::mat4 projectionMatrix;
        glm::vec3 position;
        
        float horizontalRotation;
        float verticalRotation;

    public:
        Camera(Window *window);

        void tick(float dt);

        glm::mat4 getViewMatrix();
        glm::vec3 getDirectionFacingVector();

        glm::vec3 getRightVector();
        glm::vec3 getUpVector();

    private:
        bool m_wasPaused, m_isPaused;
        Window *m_window;
    };
}
