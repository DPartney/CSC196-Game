#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{
	CLASS_DEFINITION(Player);

	bool Player::Initialize()
	{
		Actor::Initialize();

		// cache off
		m_physicsComponent = GetComponent<PhysicsComponent>();
		auto collisionComponent = GetComponent<CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;
			}
		}

		return true;
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		// movement
		float rotate = 0;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
		m_physicsComponent->ApplyTorque(rotate * turnRate);

		float thrust = 0;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
		vec2 forward = vec2{ 0, -1 }.Rotate(transform.rotation);

		m_physicsComponent->ApplyForce(forward * speed * thrust);

		transform.position.x = Wrap(transform.position.x, (float)g_renderer.GetWidth());
		transform.position.y = Wrap(transform.position.y, (float)g_renderer.GetHeight());

		// fire weapon
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			auto weapon = INSTANTIATE(Weapon, "Rocket");
			weapon->transform = { transform.position + forward * 30, transform.rotation + DegreesToRadians(10.0f), 1 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));

			weapon = INSTANTIATE(Weapon, "Rocket");
			weapon->transform = { transform.position + forward * 30, transform.rotation - DegreesToRadians(10.0f), 1 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));
		}

		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) g_time.SetTimeScale(0.5f);
		else g_time.SetTimeScale(1.0f);
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			destroyed = true;
			EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		}
	}
}