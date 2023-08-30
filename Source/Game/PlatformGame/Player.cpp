#include "Player.h"
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
		m_spriteAnimComponent = GetComponent<SpriteAnimComponent>();
		m_physicsComponent = GetComponent<PhysicsComponent>();

		return true;
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
		READ_DATA(value, maxSpeed);
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		// movement
		float dir = 0;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		bool onGround = (groundCount > 0);
		vec2 velocity = m_physicsComponent->m_velocity;

		if (dir)
		{
		velocity.x += speed * dir * ((onGround) ? 1 : 0.25f) * dt;
		velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
		m_physicsComponent->SetVelocity(velocity);
		}

		// jump
		if (onGround && g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			vec2 up = vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(velocity + (up * jump));
		}

		//m_physicsComponent->SetGravityScale((velocity.y > 0) ? 5.0f : 3.0f);

		// animation
		if (std::fabs(velocity.x) > 0.2f)
		{
			if (dir != 0) m_spriteAnimComponent->flipH = (dir < 0);
			m_spriteAnimComponent->SetSequence("run");
		}
		else
		{
			m_spriteAnimComponent->SetSequence("idle");
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			//destroyed = true;
			//EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		}

		if (other->tag == "Ground") groundCount++;
	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}
}