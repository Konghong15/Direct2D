#include "CollisionManager.h"
#include "ICollideable.h"
#include "GameObject.h"

namespace d2dFramework
{
	CollisionManager::CollisionManager()
	{
		mOnCollisionObjectIDMap.reserve(RESERVE_SIZE);
	}

	CollisionManager::~CollisionManager()
	{
		mOnCollisionObjectIDMap.clear();
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
				if (mCollideable[i]->CheckCollision(mCollideable[j], &manifold))
				{
					continue;
				}

				mEnterCollisionQueue.push({ mCollideable[i]->GetGameObject()->GetId(), mCollideable[j]->GetGameObject()->GetId(), manifold });
				manifold.CollisionNormal *= -1;
				mEnterCollisionQueue.push({ mCollideable[j]->GetGameObject()->GetId(), mCollideable[i]->GetGameObject()->GetId(), manifold });
			}
		}

		while (!mEnterCollisionQueue.empty())
		{
			auto pair = mEnterCollisionQueue.front();
			mEnterCollisionQueue.pop();

			auto iter = mOnCollisionObjectIDMap.find(std::get<0>(pair));
			if (iter == mOnCollisionObjectIDMap.end())
			{
				mOnCollisionObjectIDMap.insert(std::get<0>(pair), std::list<std::pair<unsigned int, Manifold>>());
				m
			}
			else
			{

			}

			// handle OnEnterCollision
		}

		while (!mExitCollisionQueue.empty())
		{
			auto pair = mExitCollisionQueue.front();
			mEnterCollisionQueue.pop();

			auto findLhs = mOnCollisionObjectIDMap.find(pair.first);
			auto findRhs = mOnCollisionObjectIDMap.find(pair.second);

			std::list < std::pair<unsigned int, Manifold>>& lhsList = findLhs->second;
			std::list < std::pair<unsigned int, Manifold>>& rhsList = findRhs->second;

			lhsList.erase(std::find(lhsList.begin(), lhsList.end(), findRhs->first));
			rhsList.erase(std::find(rhsList.begin(), rhsList.end(), findLhs->first));

			// handle OnExitCollision
		}
	}

	void CollisionManager::EnterCollisionCallback()
	{

	}

	void CollisionManager::OnCollsionCallback()
	{

	}

	void CollisionManager::ExitCollisionCallback()
	{

	}
}