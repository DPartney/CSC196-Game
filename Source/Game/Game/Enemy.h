#pragma once
#include "Framework/PhysicsComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
	class Enemy : public Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

			Enemy(float speed, float turnRate, const kiko::Transform& transform) :
			Actor{ transform },
			speed{ speed },
			turnRate{ turnRate }
		{
			fireRate = 2.0f;
			fireTimer = fireRate;
		} 

		Enemy() = default;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		bool Initialize() override;

	private:
		float speed = 0;
		float turnRate = 0;

		float fireRate = 0;
		float fireTimer = 0;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}