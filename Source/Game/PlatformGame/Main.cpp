#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"

#include "PlatformGame.h"

#include <functional>
#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
	std::function<int(int, int)> op;

	INFO_LOG("Initailizing Engine...");

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	// initialize engine
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	kiko::PhysicsSystem::Instance().Initialize();

	// create game
	unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
	game->Initialize();

	// main game loop
	bool quit = false;
	while (!quit)
	{
		// update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());

		// update game
		game->Update(kiko::g_time.GetDeltaTime());

		// draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		game->Draw(kiko::g_renderer);
		kiko::g_particleSystem.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();
	}

	return 0;
}