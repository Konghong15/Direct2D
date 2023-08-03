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

		// 컴포넌트가 등록된 채 콜백하여 업데이트하는 방식
		// 각자 시스템에 ID 동록해서 관련 처리하는 방식
		// 크게 렌더링과 충돌 검출, 이동처리 정도? 나머지는 고유한 시스템이나 관련스크립트로 뺴서 처리하면 될 거 같다.

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