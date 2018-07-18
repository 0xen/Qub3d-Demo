#include <qub3d\BUILD_ORDER.hpp>


int main(int argc, char **argv)
{
	Settings::GameConfig* configurations = Settings::GameConfig::Get();

	configurations->loadFromFile("assets/config.json");

	IRenderer* renderer = IRenderer::loadRenderer(Vulkan);

	IWindow* window = IWindow::loadWindow(configurations, Vulkan);

	Mesh mesh;
	mesh.vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.f));
	mesh.vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.f));
	mesh.vertices.push_back(glm::vec3(0.5f, 0.5f, 0.f));
	mesh.vertices.push_back(glm::vec3(0.5f, -0.5f, 0.f));
	mesh.vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.f));
	mesh.indices = { 0, 1, 2, 2, 3, 0 };

	while (window->isRunning())
	{
		window->pollEvents();
		renderer->render();
		window->swapBuffers();
		window->sleep(1000 / 60.f);
	}

	delete renderer;
	delete window;

    return 0;
}