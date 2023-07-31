#pragma once

#include <cassert>
#include <unordered_map>
#include <typeinfo>

namespace d2dFramework
{
	class Component;

	class GameObject
	{
	public:
		GameObject(unsigned int id);
		~GameObject();

		template <typename T>
		T* CreateComponent();
		template <typename T>
		T* GetComponent();

		// ������Ʈ�� ��ϵ� ä �ݹ��Ͽ� ������Ʈ�ϴ� ���
		// ���� �ý��ۿ� ID �����ؼ� ���� ó���ϴ� ���
		// ũ�� �������� �浹 ����, �̵�ó�� ����? �������� ������ �ý����̳� ���ý�ũ��Ʈ�� ���� ó���ϸ� �� �� ����.

		inline unsigned int GetId() const;

	private:
		unsigned int mId;
		std::unordered_map<size_t, Component*> mComponents;
	};

	template <typename T>
	T* GameObject::CreateComponent()
	{
		bool bIsBase = std::is_base_of<Component, T>::value;
		assert(bIsBase);

		T* component = new T(this);
		size_t hash = typeid(T).hash_code();
		mComponents.insert({ hash, component });

		return component;
	}

	template <typename T>
	T* GameObject::GetComponent()
	{
		size_t hash = typeid(T).hash_code();
		auto iter = mComponents.find(hash);

		if (iter == mComponents.end())
		{
			return nullptr;
		}

		T* find = static_cast<T*>((*iter).second);

		return find;
	}

	unsigned int GameObject::GetId() const
	{
		return mId;
	}
}