
#include <qub3d\BUILD_ORDER.hpp>

using namespace q3;

Camera::Camera(IWindow *window):
    m_isPaused(false),
    m_wasPaused(false),
    m_window(window),
    horizontalRotation(0.f),
    verticalRotation(0.f),
    position(glm::vec3(0.f, 0.f, 0.f))
{
    Settings::GameConfig *config = Settings::GameConfig::Get();

    SDL_ShowCursor(0);
    SDL_WarpMouseInWindow(window->getWindow(), config->WindowWidth / 2.f, config->WindowHeight / 2.f);
}

glm::vec3 Camera::getDirectionFacingVector()
{
    return glm::vec3(
        SDL_cosf(verticalRotation) * SDL_sinf(horizontalRotation),
        SDL_sinf(verticalRotation),
        SDL_cosf(verticalRotation) * SDL_cosf(verticalRotation)
    );
}

glm::mat4 Camera::getViewMatrix()
{
    glm::vec3 centre = position + getDirectionFacingVector();
    return glm::lookAt(position, centre, getUpVector());
}

glm::vec3 Camera::getRightVector()
{
    return glm::vec3(
        SDL_sinf(horizontalRotation - M_PI / 2),
        0.f,
        SDL_cosf(horizontalRotation - M_PI / 2)
    );
}

glm::vec3 Camera::getUpVector()
{
    return glm::cross(getRightVector(), getDirectionFacingVector());
}

void Camera::tick(float dt)
{
    const float cameraSpeed = 0.01f;
    const float mouseSpeed = 0.000075f;

    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    Settings::GameConfig *config = Settings::GameConfig::Get();
    
    if (!m_isPaused)
    {

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        horizontalRotation += mouseSpeed * dt * static_cast<float>(config->WindowWidth / 2.f - mouseX);
        verticalRotation += mouseSpeed * dt * static_cast<float>(config->WindowHeight / 2.f - mouseY);

        glm::vec3 dir = getDirectionFacingVector();
        glm::vec3 right = getRightVector();

        if (keyboardState[SDL_SCANCODE_W]) position += dir * dt * cameraSpeed;
        else if (keyboardState[SDL_SCANCODE_S]) position -= dir * dt * cameraSpeed;

        if (keyboardState[SDL_SCANCODE_D]) position += right * dt * cameraSpeed;
        else if (keyboardState[SDL_SCANCODE_A]) position -= right * dt * cameraSpeed;

        if (keyboardState[SDL_SCANCODE_SPACE]) position.y += dt * cameraSpeed;
        else if (keyboardState[SDL_SCANCODE_LCTRL]) position.y -= dt * cameraSpeed;
    }

    if (keyboardState[SDL_SCANCODE_ESCAPE])
    {
        if (!m_wasPaused)
        {
            m_isPaused = !m_isPaused;
            SDL_ShowCursor(m_isPaused);

            if (!m_isPaused)
            {
                SDL_WarpMouseInWindow(m_window->getWindow(), config->WindowWidth / 2.f, config->WindowHeight / 2.f);
                SDL_SetWindowTitle(m_window->getWindow(), "Qub3d");
            }
            else
            {
                SDL_SetWindowTitle(m_window->getWindow(), "Qub3d - Paused");
            }
        }
        
        m_wasPaused = true;
    }
    else {
        m_wasPaused = false;
    }
}