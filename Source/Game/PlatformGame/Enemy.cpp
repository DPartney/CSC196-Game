#include "Enemy.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "Player.h"

namespace kiko
{
	CLASS_DEFINITION(Enemy);

	bool Enemy::Initialize()
	{
		Actor::Initialize();

		// cache off
		m_physicsComponent = GetComponent<PhysicsComponent>();

		return true;
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		// movement
		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}

	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			destroyed = true;
			EventManager::Instance().DispatchEvent("OnEnemyDead", 0);
		}
	}

	void Enemy::OnCollisionExit(Actor* other)
	{
		
	}
}