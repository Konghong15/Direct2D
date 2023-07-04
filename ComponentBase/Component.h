#pragma once

#include <cassert>

namespace componentBase
{
	class GameObject;
	class System;

	class Component
	{
	public:
		Component(GameObject* gameObject)
			: mOwnerObject(gameObject)
		{
		}
		virtual ~Component() = 0;

		virtual void RegisterSystem(System* system);

	protected:
		inline GameObject* GetGameObject();

	private:
		GameObject* mOwnerObject;
	};

	GameObject* Component::GetGameObject()
	{
		assert(mOwnerObject != nullptr);
		return mOwnerObject;
	}
}