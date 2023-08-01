#pragma once

#include <unordered_map>
#include <queue>

#include "Manifold.h"

namespace d2dFramework
{
	class ICollideable;

	class CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();
		CollisionManager(const CollisionManager&) = delete;
		CollisionManager& operator=(const CollisionManager&) = delete;

		void Update();

		void EnterCollisionCallback();
		void OnCollsionCallback();
		void ExitCollisionCallback();

		inline void RegisterCollideable(ICollideable* collideable);
		inline void UnregisterCollideable(ICollideable* collideable);

	private:
		enum { RESERVE_SIZE = 4096 };

		std::unordered_map<unsigned int, std::list<std::pair<unsigned int, Manifold>>> mOnCollisionObjectIDMap;
		std::queue<std::tuple<unsigned int, unsigned int, Manifold>> mEnterCollisionQueue;
		std::queue<std::pair<unsigned int, unsigned int>> mExitCollisionQueue;

		std::vector<ICollideable*> mCollideable;
		std::vector<ICollideable*> mCreateCollideable;
	};

	void CollisionManager::RegisterCollideable(ICollideable* collideable)
	{
		mCreateCollideable.push_back(collideable);
	}

	void CollisionManager::UnregisterCollideable(ICollideable* collideable)
	{
		mCollideable.erase(std::find(mCollideable.begin(), mCollideable.end(), collideable));
	}
}