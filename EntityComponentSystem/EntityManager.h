#pragma once

#include <vector>

namespace entityComponentSystem
{
	class Entity;

	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();
		EntityManager(const EntityManager& other) = delete;
		EntityManager& operator=(const EntityManager& other) = delete;

		Entity* CreateEntity(unsigned int entityId);
		void DestroyEntity(unsigned int entityId);
		Entity* GetEntityByIdOrNull(unsigned int entityId);

		inline std::vector<Entity*>& GetEntity();

	private:
		enum { RESERVE_SIZE = 512 };
		std::vector<Entity*> mEntities;
	};

	std::vector<Entity*>& EntityManager::GetEntity()
	{
		return mEntities;
	}
}