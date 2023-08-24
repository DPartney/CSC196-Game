#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "PlatformGame.h"

bool PlatformGame::Initialize()
{

	// load audio
	kiko::g_audioSystem.AddAudio("hit", "hit.wav");

	// create scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("scenes/PlatformScene.json");
	m_scene->Initialize();

	// add events
	EVENT_SUBSCRIBE("AddPoints", PlatformGame::AddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);

	return true;
}

void PlatformGame::Shutdown()
{
}

void PlatformGame::Update(float dt)
{
	switch (m_state)
	{
	case PlatformGame::eState::Title:
		m_scene->GetActorByName("Title")->active = true;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_scene->GetActorByName("Title")->active = false;
			m_state = eState::StartGame;
		}
		break;

	case PlatformGame::eState::StartGame:
		
		break;

	case PlatformGame::eState::StartLevel:
		
		break;
	case PlatformGame::eState::Game:
		
		break;

	case eState::PlayerDeadStart:
		
		break;

	case PlatformGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;

	case PlatformGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scene->Update(dt);
}

void PlatformGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void PlatformGame::AddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const kiko::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}