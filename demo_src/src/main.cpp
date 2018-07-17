#include <qub3d\BUILD_ORDER.hpp>


int main(int argc, char **argv)
{
	Settings::GameConfig* configurations = Settings::GameConfig::Get();

	configurations->loadFromFile("assets/config.json");
	
	IEngine* engine = IEngine::LoadEngine(configurations,GL11);

	while (engine->IsRunning())
	{
		engine->Render();
	}

	delete engine;

    return 0;
}