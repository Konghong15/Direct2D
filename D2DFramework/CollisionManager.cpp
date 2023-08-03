#include "CollisionManager.h"

#include "eFrameworkID.h"
#include "EventManager.h"

namespace d2dFramework
{
	CollisionManager::CollisionManager()
		: BaseEntity(static_cast<unsigned int>(eFramworkID::CollisionManager))
	{
		mOnCollisionObjectMap.reserve(RESERVE_SIZE);
	}

	CollisionManager::~CollisionManager()
	{
		Release();
	}

	void CollisionManager::Update()
	{
		for (size_t i = 0; i < mCollideable.size(); ++i)
		{
			mCollideable[i]->UpdateCollider();
		}

		Manifold manifold;
		for (size_t i = 0; i < mCollideable.size(); ++i)
		{
			for (size_t j = i + 1; j < mCollideable.size(); ++j)
			{
				unsigned int lhsId = mCollideable[i]->GetGameObject()->GetId();
				unsigned int rhsId = mCollideable[j]->GetGameObject()->GetId();

				if (!mCollideable[i]->CheckCollision(mCollideable[j], &manifold))
				{
					auto lhsIter = mOnCollisionObjectMap.find(lhsId);
			
					if (lhsIter->second.find(rhsId) != lhsIter->second.end())
					{
						mExitCollisionQueue.push({ lhsId, rhsId });
					}

					continue;
				}

				mCollideable[i]->OnCollision(mCollideable[j], manifold);

				mEnterCollisionQueue.push({ lhsId, rhsId , manifold });
				manifold.CollisionNormal *= -1;
				mEnterCollisionQueue.push({ rhsId, lhsId, manifold });

				// EventManager::GetInstance()->SendEvent("OnCollision", lhsId, "");
				// EventManager::GetInstance()->SendEvent("OnCollision", rhsId, "");
			}
		}

		while (!mEnterCollisionQueue.empty())
		{
			auto tuple = mEnterCollisionQueue.front();
			mEnterCollisionQueue.pop();

			unsigned int lhsId = std::get<0>(tuple);
			unsigned int rhsId = std::get<1>(tuple);
			Manifold manifold = std::get<2>(tuple);

			auto lhsIter = mOnCollisionObjectMap.find(lhsId);
			assert(lhsIter != mOnCollisionObjectMap.end());

			std::unordered_map<unsigned int, Manifold>& collisionDataMap = lhsIter->second;
			collisionDataMap.insert(std::make_pair(rhsId, manifold));

			// EventManager::GetInstance()->SendEvent("EnterCollision", lhsId, "");
		}

		while (!mExitCollisionQueue.empty())
		{
			auto pair = mExitCollisionQueue.front();
			mExitCollisionQueue.pop();

			unsigned int lhsId = pair.first;
			unsigned int rhsId = pair.second;

			auto findLhs = mOnCollisionObjectMap.find(lhsId);
			auto findRhs = mOnCollisionObjectMap.find(rhsId);

			std::unordered_map<unsigned int, Manifold>& lhsCollisionDataMap = findLhs->second;
			std::unordered_map<unsigned int, Manifold>& rhsCollisionDataMap = findRhs->second;

			lhsCollisionDataMap.erase(findRhs->first);
			rhsCollisionDataMap.erase(findLhs->first);

			// EventManager::GetInstance()->SendEvent("ExitCollision", lhsId, "");
			// EventManager::GetInstance()->SendEvent("ExitCollision", rhsId, "");
		}
	}

	void CollisionManager::Release()
	{
		mOnCollisionObjectMap.clear();

		while (!mEnterCollisionQueue.empty())
		{
			mEnterCollisionQueue.pop();
		}

		while (!mExitCollisionQueue.empty())
		{
			mExitCollisionQueue.pop();
		}
	}
}