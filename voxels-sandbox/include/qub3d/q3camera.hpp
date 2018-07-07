#pragma once
#include <glm/glm.hpp>
#include <SDL.h>

class Q3Camera {
public:
    void update(float dt);
    void glLook();

    Q3Camera(SDL_Window *window);

private:
    glm::vec3 m_position;
    glm::vec3 m_up;
    glm::vec3 m_dir;

    float m_hAngle;
    float m_vAngle;
    
    float m_speed = 0.01f;
    float m_mouseSpeed = 0.000075f;

    SDL_Window *m_window;
};