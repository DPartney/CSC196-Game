#pragma once
#include "PhysicsComponent.h"

namespace kiko
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		void Update(float dt) override;
		void ApplyForce(const vec2& force) override;

	public:
		vec2 m_velocity;
		vec2 m_acceleration;
		float m_mass = 1.0f;
		float m_damping = 0;
	};
}