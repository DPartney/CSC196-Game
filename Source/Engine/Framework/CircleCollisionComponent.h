#pragma once
#include "CollisionComponent.h"

namespace kiko
{
	class CircleCollisionComponent : public CollisionComponent
	{
	public:
		bool CheckCollision(CollisionComponent* collision);
		virtual void Update(float dt) override;
	};
}