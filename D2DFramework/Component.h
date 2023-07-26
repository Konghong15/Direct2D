#pragma once

namespace d2dFramework
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* owner) : mOwner(owner) {}
		virtual ~Component() = default;

	protected:
		inline GameObject* GetGameObject() const;

	private:
		GameObject* mOwner;
	};

	GameObject* Component::GetGameObject() const
	{
		return mOwner;
	}
}