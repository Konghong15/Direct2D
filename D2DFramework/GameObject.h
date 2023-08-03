#pragma once

#include "BaseEntity.h"

#include <cassert>
#include <unordered_map>
#include <typeinfo>

namespace d2dFramework
{
	class Component;

	class GameObject : public BaseEntity
	{
		friend class ObjectManager;

	public:
		void Init();
		void Release();

		template <typename T>
		T* CreateComponent(unsigned int id);
		template <typename T>
		T* GetComponent();

		// ������Ʈ�� ��ϵ� ä �ݹ��Ͽ� ������Ʈ�ϴ� ���
		// ���� �ý��ۿ� ID �����ؼ� ���� ó���ϴ� ���
		// ũ�� �������� �浹 ����, �̵�ó�� ����? �������� ������ �ý����̳� ���ý�ũ��Ʈ�� ���� ó���ϸ� �� �� ����.

	private:
		GameObject(unsigned int id);
		~GameObject();

	private:
		std::unordered_map<size_t, Component*> mComponents;
	};

	template <typename T>
	T* GameObject::CreateComponent(unsigned int id)
	{
		bool bIsBase = std::is_base_of<Component, T>::value;
		assert(bIsBase);

		T* component = new T(id, this);
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
}