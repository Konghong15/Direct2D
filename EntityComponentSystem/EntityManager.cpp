#include "Entity.h"
#include "EntityManager.h"

namespace entityComponentSystem
{
	EntityManager::EntityManager()
	{
		mEntities.reserve(RESERVE_SIZE);
	}

	EntityManager::~EntityManager()
	{
		for (auto iter = mEntities.begin(); iter != mEntities.end(); ++iter)
		{
			delete (*iter);
		}

		mEntities.clear();
	}

	Entity* EntityManager::CreateEntity(unsigned int entityId)
	{
		Entity* entity = new Entity(entityId);
		mEntities.push_back(entity);

		return entity;
	}

	void EntityManager::DestroyEntity(unsigned int entityId)
	{
		for (auto iter = mEntities.begin(); iter != mEntities.end(); ++iter)
		{
			if ((*iter)->GetEntityId() == entityId)
			{
				delete (*iter);
				mEntities.erase(iter);

				break;
			}
		}
	}

	Entity* EntityManager::GetEntityByIdOrNull(unsigned int entityId)
	{
		for (auto iter = mEntities.begin(); iter != mEntities.end(); ++iter)
		{
			if ((*iter)->GetEntityId() == entityId)
			{
				return (*iter);
			}
		}

		return nullptr;
	}
}