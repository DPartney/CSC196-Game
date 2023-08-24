#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

bool SpaceGame::Initialize()
{
	// create font / text objects

	m_font = GET_RESOURCE(kiko::Font, "arcadeclassic.ttf", 24);
	m_scoreText = std::make_unique<kiko::Text>(m_font);
	m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	m_titleText = std::make_unique<kiko::Text>(m_font);

	m_gameoverText = std::make_unique<kiko::Text>(m_font);
	m_gameoverText->Create(kiko::g_renderer, "GAME OVER", kiko::Color{ 1, 1, 1, 1 });

	m_timerText = std::make_unique<kiko::Text>(m_font);
	m_timerText->Create(kiko::g_renderer, "TIMER", kiko::Color{ 1, 1, 1, 1 });

	// load audio
	kiko::g_audioSystem.AddAudio("hit", "hit.wav");

	// create scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("scenes/SpaceScene.json");
	m_scene->Initialize();

	// add events
	EVENT_SUBSCRIBE("AddPoints", SpaceGame::AddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		m_scene->GetActorByName("Title")->active = true;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_scene->GetActorByName("Title")->active = false;
			m_state = eState::StartGame;
		}
		break;

	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;

	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
		{
			auto player = INSTANTIATE(Player, "Player");
			player->transform = kiko::Transform{ { 400, 300 }, 0, 1 };
			player->Initialize();
			m_scene->Add(std::move(player));
		}
		m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_gameTimer += dt;
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->transform = kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 1 };
			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}
		break;

	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;

	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;

	case SpaceGame::eState::GameOver:
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

	m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
	m_timerText->Create(kiko::g_renderer, std::to_string((int)m_gameTimer), { 1, 1, 1, 1 });
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 350, 300);
	}
	if (m_state == eState::GameOver)
	{
		m_gameoverText->Draw(renderer, 400, 300);
	}

	m_timerText->Draw(renderer, 400, 40);
	m_scoreText->Draw(renderer, 40, 20);
}

void SpaceGame::AddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const kiko::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}