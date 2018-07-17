#pragma once

#include <qub3d/IRenderer.hpp>

class GL11Engine : public IEngine
{
public:
	GL11Engine(Settings::GameConfig* config);
	bool Start();
	void Stop();
	void Render();
	void Update();
private:
	Mesh mesh;
};