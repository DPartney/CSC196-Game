#pragma once
#include "Framework/Actor.h"
#include "Framework/PhysicsComponent.h"

namespace kiko
{
	class Player : public Actor
	{
	public:
		CLASS_DECLARATION(Player)

		Player(float speed, float turnRate, const kiko::Transform& transform) :
			Actor{ transform },
			speed{ speed },
			turnRate{ turnRate }
		{}

		Player() = default;

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		float speed = 0;
		float turnRate = 0;

		PhysicsComponent* m_physicsComponent = nullptr;
	};
}