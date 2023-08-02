#pragma once

#include "BaseEntity.h"
#include "ICollideable.h"
#include "GameObject.h"
#include "Manifold.h"

#include <cassert>
#include <unordered_map>
#include <queue>

namespace d2dFramework
{
	class CollisionManager final : public BaseEntity
	{
	public:
		CollisionManager();
		~CollisionManager();
		CollisionManager(const CollisionManager&) = delete;
		CollisionManager& operator=(const CollisionManager&) = delete;

		void Update();
		void Release();

		inline void RegisterCollideable(ICollideable* collideable);
		inline void UnregisterCollideable(ICollideable* collideable);

		inline const Manifold& GetManifold(unsigned int lhsId, unsigned int rhsId) const;

	private:
		enum { RESERVE_SIZE = 4096 };

		std::unordered_map<unsigned int, std::unordered_map<unsigned int, Manifold>> mOnCollisionObjectMap;
		std::queue<std::tuple<unsigned int, unsigned int, Manifold>> mEnterCollisionQueue;
		std::queue<std::pair<unsigned int, unsigned int>> mExitCollisionQueue;

		std::vector<ICollideable*> mCollideable;
		std::vector<ICollideable*> mCreateCollideable;
	};

	void CollisionManager::RegisterCollideable(ICollideable* collideable)
	{
		mCreateCollideable.push_back(collideable);
		mOnCollisionObjectMap.insert({ collideable->GetGameObject()->GetId(), std::unordered_map<unsigned int, Manifold>() });
	}

	void CollisionManager::UnregisterCollideable(ICollideable* collideable)
	{
		mCollideable.erase(std::find(mCollideable.begin(), mCollideable.end(), collideable));
		mOnCollisionObjectMap.erase(collideable->GetGameObject()->GetId());
	}

	const Manifold& CollisionManager::GetManifold(unsigned int lhsId, unsigned int rhsId) const
	{
		auto mapIter = mOnCollisionObjectMap.find(lhsId);
		assert(mapIter != mOnCollisionObjectMap.end());

		const std::unordered_map<unsigned int, Manifold>& collisionDataMap = mapIter->second;
		auto dataIter = collisionDataMap.find(rhsId);
		assert(dataIter != collisionDataMap.end());

		return dataIter->second;
	}
}