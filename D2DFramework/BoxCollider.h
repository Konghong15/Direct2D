#pragma once

#include "Component.h"
#include "ICollideable.h"
#include "Vector2.h"

namespace d2dFramework
{
	class GameObject;

	class BoxCollider : public Component, public ICollideable
	{
	public:
		BoxCollider(GameObject* owner);
		virtual ~BoxCollider() = default;

		virtual void CheckCollision(ICollideable* other);
		inline virtual const hRectangle& GetCollider();

	private:
		bool mbIsCollision;

		Vector2 mSize;
		Vector2 mOffset;
	};

	const hRectangle& BoxCollider::GetCollider();

}