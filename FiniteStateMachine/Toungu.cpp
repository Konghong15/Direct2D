#include "Toungu.h"

namespace finiteStateMachine
{
	Toungu::Toungu(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float speed, float distance)
		: Weapon(animationInstance, rectangle, speed, distance)
	{
	}

	void Toungu::Update(float deltaTime)
	{
		if (mWeaponState == eWeaponState::Idle)
		{
			//mTranslate.SetXY(0.f, 0.f);

			if (mParent != nullptr)
			{
				mTransform = combineMatrix() * mParent->GetTrasform();
			}
			else
			{
				mTransform = combineMatrix();
			}
		}
		else if (mMaxDistance < mTranslate.GetMagnitude())
		{
			mWeaponState = eWeaponState::Idle;
		}
		else
		{
			mScale.Move(deltaTime, 0);
			mTransform = combineMatrix() * mPrevParentMatrix;
		}

		for (Object* child : mChildren)
		{
			child->Update(deltaTime);
		}
	}
}