#pragma once
#include "Framework/SpriteAnimComponent.h"
#include "Framework/PhysicsComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
	class Player : public Actor
	{
	public:
		CLASS_DECLARATION(Player)

			Player(float speed, float jump, const kiko::Transform& transform) :
			Actor{ transform },
			speed{ speed },
			jump{ jump }
		{}

		Player() = default;

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float speed = 0;
		float jump = 0;
		float maxSpeed = 0;
		int groundCount = 0;

		SpriteAnimComponent* m_spriteAnimComponent = nullptr;
		PhysicsComponent* m_physicsComponent = nullptr;
	};
}