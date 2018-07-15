#include <qub3d/window.hpp>
#include <qub3d/settings.hpp>

#include <qub3d/renderer.hpp>

#include <nlohmann/json.hpp>
#include <fstream>

int main(int argc, char **argv)
{
    Settings::GameConfig *configurations = Settings::GameConfig::Get();
    configurations->loadFromFile("assets/config.json");

    Window window("Qub3d", configurations->WindowWidth, configurations->WindowHeight);
    
    IRenderer *renderer = new GL11Renderer();

    Mesh mesh;
    mesh.vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.f));
    mesh.vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.f));
    mesh.vertices.push_back(glm::vec3(0.5f, 0.5f, 0.f));
    mesh.vertices.push_back(glm::vec3(0.5f, -0.5f, 0.f));
    mesh.vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.f));
    mesh.indices = { 0, 1, 2, 2, 3, 0 };


    while (window.isRunning())
    {
        window.pollEvents();
        renderer->renderMesh(&mesh);
        window.swapBuffers();
        window.sleep(1000 / 60.f);
    }

    return 0;
}