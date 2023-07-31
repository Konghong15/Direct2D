#pragma once

#include <unordered_map>

namespace d2dFramework
{
	class GameObject;

	class ObjectManager
	{
	public:
		ObjectManager();
		~ObjectManager();

		inline GameObject* CreateObject(unsigned int id);
		inline void DeletObject(unsigned int id);

	private:
		enum { RESERVE_SIZE = 4096 };

		std::unordered_map<unsigned int, GameObject*> mObjectMap;
	};

	GameObject* ObjectManager::CreateObject(unsigned int id)
	{

	}

	void ObjectManager::DeletObject(unsigned int id)
	{

	}
}