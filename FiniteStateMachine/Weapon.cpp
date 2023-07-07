#include <cassert>

#include "Weapon.h"
#include "AnimationInstance.h"

namespace finiteStateMachine
{
	Weapon::Weapon(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float speed, float distance)
		: Object(rectangle)
		, mAnimationInstnace(animationInstance)
		, mSpeed(speed)
		, mWeaponState(eWeaponState::Idle)
		, mPrevParentMatrix(gameProcessor::Matrix3X3::Identity())
		, mMaxDistance(distance)
		, mInitTraslate(mTranslate)
	{
	}

	Weapon::~Weapon()
	{
		delete mAnimationInstnace;
	}

	void Weapon::HandleState()
	{
		switch (mWeaponState)
		{
		case finiteStateMachine::eWeaponState::Idle:
			break;
		case finiteStateMachine::eWeaponState::Action:
			if (mElapsedDistance >= mMaxDistance)
			{
				mWeaponState = eWeaponState::Back;

				float remainder = mElapsedDistance - mMaxDistance;
				mDirection.SetXY(-mDirection.GetX(), -mDirection.GetY());
				mTranslate.Move(mDirection.GetX() * remainder, mDirection.GetY() * remainder);
			}
			break;
		case finiteStateMachine::eWeaponState::Back:
			mDirection = mParent->GetWorldRectangle().GetCenter() - GetWorldRectangle().GetCenter();
			if (mDirection.GetMagnitude() < 10.f)
			{
				mWeaponState = eWeaponState::Idle;
				mTranslate = mInitTraslate;
			}

			mDirection.Normalize();
			break;
		default:
			assert(false);
			break;
		}
	}

	void Weapon::Update(float deltaTime)
	{
		if (mWeaponState == eWeaponState::Idle)
		{
			if (mParent != nullptr)
			{
				mTransform = combineMatrix() * mParent->GetTrasform();
			}
			else
			{
				mTransform = combineMatrix();
			}
		}
		else
		{
			mRotateInRadian += 3.14f * 4 * deltaTime;

			gameProcessor::Vector2 velocity = mDirection * mSpeed * deltaTime;
			mElapsedDistance += velocity.GetMagnitude();
			mTranslate.Move(velocity.GetX(), velocity.GetY());
			mTransform = combineMatrix() * mPrevParentMatrix;
		}

		for (Object* child : mChildren)
		{
			child->Update(deltaTime);
		}
	}

	void Weapon::Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& compositeTrasform)
	{
		mAnimationInstnace->Render(renderManager, mRectangle, gameProcessor::Matrix3X3::ComineMatrix(3, gameProcessor::Matrix3X3::GetScale(1, -1), mTransform, compositeTrasform));

		for (Object* child : mChildren)
		{
			child->Render(renderManager, compositeTrasform);
		}
	}

	void Weapon::Action(const gameProcessor::Vector2& direction)
	{
		if (mWeaponState == eWeaponState::Idle)
		{
			mPrevParentMatrix = mParent->GetTrasform();
			mDirection = direction;
			mWeaponState = eWeaponState::Action;
			mElapsedDistance = 0.f;
		}
	}
}