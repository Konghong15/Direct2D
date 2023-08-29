#include "PlatformComponent.h"

#include "GameObject.h"
#include "Transform.h"
#include "MathHelper.h"

namespace d2dRigidbodyAABB
{
	PlatformComponent::PlatformComponent(unsigned int id, d2dFramework::GameObject* owner)
		: Component(id, owner)
	{
	}

	void PlatformComponent::Init()
	{
		IUpdateable::Init();
	}
	void PlatformComponent::Update(float deltaTime)
	{
		using namespace d2dFramework;

		if (mMovePositions.size() == 0)
		{
			return;
		}
		if (mbIsMovePaused)
		{
			return;
		}

		mElpasedMoveTime += deltaTime * mMoveRatio;

		if (mElpasedMoveTime >= 1.f)
		{
			mCurrentPositionIndex = (mCurrentPositionIndex + 1) % mMovePositions.size();
			mElpasedMoveTime -= 1.f;
		}

		unsigned int nextPositionIndex = (mCurrentPositionIndex + 1) % mMovePositions.size();
		assert(mCurrentPositionIndex < mMovePositions.size());
		assert(nextPositionIndex < mMovePositions.size());
		const Vector2& start = mMovePositions[mCurrentPositionIndex];
		const Vector2& end = mMovePositions[nextPositionIndex];
		Vector2 current =
		{
			MathHelper::GetInterpolation(start.GetX(), end.GetX(), mElpasedMoveTime),
			MathHelper::GetInterpolation(start.GetY(), end.GetY(), mElpasedMoveTime)
		};

		Transform* transform = GetGameObject()->GetComponent<Transform>();
		transform->SetTranslate(current);
	}
	void PlatformComponent::Release()
	{
		IUpdateable::Release();
	}
}