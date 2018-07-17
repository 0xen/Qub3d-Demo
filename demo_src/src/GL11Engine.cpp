#include <qub3d\BUILD_ORDER.hpp>

GL11Engine::GL11Engine(Settings::GameConfig* config)
{
	// Temp mesh
	mesh.vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.f));
	mesh.vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.f));
	mesh.vertices.push_back(glm::vec3(0.5f, 0.5f, 0.f));
	mesh.vertices.push_back(glm::vec3(0.5f, -0.5f, 0.f));
	mesh.vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.f));
	mesh.indices = { 0, 1, 2, 2, 3, 0 };
	m_window = new GL11Window("Qub3d", config->WindowWidth, config->WindowHeight);
	m_renderer = new GL11Renderer();
}

bool GL11Engine::Start()
{
	return true;
}

void GL11Engine::Stop()
{

}

void GL11Engine::Render()
{
	m_window->pollEvents();
	m_renderer->renderMesh(&mesh);
	m_window->swapBuffers();
	m_window->sleep(1000 / 60.f);
}

void GL11Engine::Update()
{
}
