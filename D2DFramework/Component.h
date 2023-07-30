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
		virtual inline GameObject* GetGameObject() const; // �ٸ� �������̽����� �Լ� �����ϱ� ���ؼ� virtual�� ����

	private:
		GameObject* mOwner;
	};

	GameObject* Component::GetGameObject() const
	{
		return mOwner;
	}
}