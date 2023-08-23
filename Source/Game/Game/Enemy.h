#pragma once
#include "Framework/PhysicsComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
	class Enemy : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

			Enemy(float speed, float turnRate, const kiko::Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{
			m_fireRate = 2.0f;
			m_fireTimer = m_fireRate;
		}

		void Update(float dt) override;
		void OnCollision(Actor* other) override;
		bool Initialize() override;

	private:
		float m_speed = 0;
		float m_turnRate = 0;

		float m_fireRate = 0;
		float m_fireTimer = 0;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}