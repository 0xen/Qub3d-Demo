#include <qub3d\BUILD_ORDER.hpp>

IEngine::~IEngine()
{
	delete m_window;
	delete m_renderer;
}

IEngine* IEngine::LoadEngine(Settings::GameConfig* config, RenderingAPI api)
{
	switch (api)
	{
	case GL11:
		return new GL11Engine(config);
		break;
	case GL3:
		break;
	case Vulkan:
		return new VulkanEngine();
		break;
	}
	return nullptr;
}

IWindow* IEngine::GetWindow()
{
	return m_window;
}

bool IEngine::IsRunning()
{
	return m_window != nullptr && m_window->isRunning();
}

IEngine::IEngine()
{
	m_running = false;
}