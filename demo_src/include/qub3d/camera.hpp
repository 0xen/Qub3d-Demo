#pragma once
#include <qub3d\BUILD_ORDER.hpp>

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
        Camera(IWindow *window);

        void tick(float dt);

        glm::mat4 getViewMatrix();
        glm::vec3 getDirectionFacingVector();

        glm::vec3 getRightVector();
        glm::vec3 getUpVector();

    private:
        bool m_wasPaused, m_isPaused;
        IWindow *m_window;
    };
}
