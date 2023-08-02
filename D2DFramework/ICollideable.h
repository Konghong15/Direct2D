#pragma once

#include "eColliderType.h"

#include <cassert>

namespace d2dFramework
{
	class hRectangle;
	class GameObject;
	class CollisionManager;
	struct Manifold;

	class ICollideable
	{
		friend class GameProcessor;

	public:
		ICollideable() = default;
		virtual ~ICollideable() = default;

		virtual void Init() = 0;
		virtual void UpdateCollider() = 0;
		virtual bool CheckCollision(ICollideable* other, Manifold* outManifold) = 0;
		virtual void OnCollision(ICollideable* other, const Manifold& manifold) = 0;
		virtual void Release() = 0;

		virtual inline GameObject* GetGameObject() const = 0;
		virtual inline eColliderType GetColliderType() const = 0;

	protected:
		inline CollisionManager* GetCollisionManager();

	private:
		static void SetCollisionManager(CollisionManager* collisionManager);

	private:
		static CollisionManager* mCollisionManager;
	};

	CollisionManager* ICollideable::GetCollisionManager()
	{
		assert(mCollisionManager != nullptr);
		return mCollisionManager;
	}
}