#pragma once
#include "Framework/Actor.h"
#include "Framework/PhysicsComponent.h"

namespace kiko
{
	class Enemy : public Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

			Enemy(float speed, float jump, const kiko::Transform& transform) :
			Actor{ transform },
			speed{ speed },
			jump{ jump }
		{}

		Enemy() = default;

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float speed = 0;
		float jump = 0;
		int groundCount = 0;

		PhysicsComponent* m_physicsComponent = nullptr;
	};
}