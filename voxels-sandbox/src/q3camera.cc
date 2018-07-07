#pragma once

#include <qub3d/q3camera.hpp>
#include <qub3d/shared_constants.hpp>
#include <qub3d/q3opengl.hpp>

Q3Camera::Q3Camera(SDL_Window *window) : m_hAngle(0.f), m_vAngle(0.f), m_position(0.f, 0.f, -10.f), m_window(window) {
    SDL_ShowCursor(0);
    SDL_WarpMouseInWindow(window, Q3_WINDOWWIDTH / 2, Q3_WINDOWHEIGHT / 2);
}

bool s_isPaused = false, s_wasPaused = false;

void Q3Camera::update(float dt) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (!s_isPaused) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        SDL_WarpMouseInWindow(NULL, Q3_WINDOWWIDTH / 2, Q3_WINDOWHEIGHT / 2);

        m_hAngle += m_mouseSpeed * dt * float(Q3_WINDOWWIDTH / 2 - x);
        m_vAngle += m_mouseSpeed * dt * float(Q3_WINDOWHEIGHT / 2 - y);
    
        m_dir = glm::vec3(
            SDL_cosf(m_vAngle) * SDL_sinf(m_hAngle),
            SDL_sinf(m_vAngle),
            SDL_cosf(m_vAngle) * SDL_cosf(m_hAngle)
        );

        glm::vec3 right(
            SDL_sinf(m_hAngle - M_PI / 2.f),
            0,
            SDL_cosf(m_hAngle - M_PI / 2.f)
        );

        m_up = glm::cross(right, m_dir);
    
        if (state[SDL_SCANCODE_W]) m_position += m_dir * dt * m_speed;
        if (state[SDL_SCANCODE_S]) m_position -= m_dir * dt * m_speed;
        if (state[SDL_SCANCODE_D]) m_position += right * dt * m_speed;
        if (state[SDL_SCANCODE_A]) m_position -= right * dt * m_speed;
        if (state[SDL_SCANCODE_SPACE]) m_position.y += dt * m_speed;
        if (state[SDL_SCANCODE_LCTRL]) m_position.y -= dt * m_speed;
    }

    if (state[SDL_SCANCODE_ESCAPE]) {
        if (!s_wasPaused) {
            s_isPaused = !s_isPaused;
            SDL_ShowCursor(s_isPaused);

            if (!s_isPaused) {
                SDL_WarpMouseInWindow(m_window, Q3_WINDOWWIDTH / 2, Q3_WINDOWHEIGHT / 2);
                SDL_SetWindowTitle(m_window, Q3_WINDOWTITLE);
            }
            else {
                SDL_SetWindowTitle(m_window, Q3_WINDOWTITLE_PAUSED);
            }
        }
        s_wasPaused = true;
    }
    else {
        s_wasPaused = false;
    }
}

void Q3Camera::glLook() {
    glm::vec3 center = m_position + m_dir;
    gluLookAt(m_position.x, m_position.y, m_position.z, center.x, center.y, center.z, m_up.x, m_up.y, m_up.z);
}