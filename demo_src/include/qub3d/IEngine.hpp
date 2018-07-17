#pragma once

#include <qub3d/IRenderer.hpp>

enum RenderingAPI
{
	GL11,
	GL3,
	Vulkan
};

class IEngine
{
public:
	~IEngine();
	// Loads the engine factory function
	// Rendering API needs to be moved into game config
	static IEngine* LoadEngine(Settings::GameConfig* config, RenderingAPI api);
	IWindow* GetWindow();
	//Interface classes
	virtual bool Start() = 0;
	virtual void Stop() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	bool IsRunning();
protected:
	IEngine();
	IWindow* m_window;
	IRenderer* m_renderer;
private:
	bool m_running;
};