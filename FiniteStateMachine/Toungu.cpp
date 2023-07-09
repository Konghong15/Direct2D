#include "Toungu.h"
#include "AnimationInstance.h"
#include "RenderManger.h"

namespace finiteStateMachine
{
	Toungu::Toungu(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float colliderArea, float speed, float distance)
		: Weapon(animationInstance, rectangle, colliderArea, speed, distance, eOwnerType::Enemy)
	{
	}

	void Toungu::HandleState()
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
				mTranslate.Move(-mDirection.GetX() * remainder, -mDirection.GetY() * remainder);
			}
			break;
		case finiteStateMachine::eWeaponState::Back:
			if (mElapsedDistance < 0.f)
			{
				float remainder = mElapsedDistance - mMaxDistance;
				mTranslate.Move(mDirection.GetX() * remainder, mDirection.GetY() * remainder);
				mWeaponState = eWeaponState::Idle;
				mTranslate = mInitTraslate;
			}
			break;
		default:
			assert(false);
			break;
		}
	}

	void Toungu::Update(float deltaTime)
	{
		if (mWeaponState == eWeaponState::Action)
		{
			gameProcessor::Vector2 velocity = mDirection * mSpeed * deltaTime;
			mElapsedDistance += velocity.GetMagnitude();
			mTranslate.Move(velocity.GetX(), velocity.GetY());
		}
		else if (mWeaponState == eWeaponState::Back)
		{
			gameProcessor::Vector2 velocity = mDirection * mSpeed * deltaTime;
			mElapsedDistance -= velocity.GetMagnitude();
			mTranslate.Move(-velocity.GetX(), -velocity.GetY());
		}

		if (mParent != nullptr)
		{
			mTransform = combineMatrix() * mParent->GetTrasform();
		}
		else
		{
			mTransform = combineMatrix();
		}

		for (Object* child : mChildren)
		{
			child->Update(deltaTime);
		}
	}

	void Toungu::Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& compositeTrasform)
	{
		if (mWeaponState != eWeaponState::Idle)
		{
			//gameProcessor::Matrix3X3 translateMatrix = gameProcessor::Matrix3X3::ComineMatrix(3, gameProcessor::Matrix3X3::GetScale(mDirection.GetX() <= 0 ? 1 : -1, -1), mTransform, compositeTrasform);
			gameProcessor::Matrix3X3 nonTranslateMatrix = gameProcessor::Matrix3X3::ComineMatrix(4, gameProcessor::Matrix3X3::GetScale(-1, -1), mTransform, gameProcessor::Matrix3X3::GetTranslate(mInitTraslate.GetX() - mTranslate.GetX(), mInitTraslate.GetY() - mTranslate.GetY()), compositeTrasform);
			gameProcessor::Matrix3X3 translateMatrix = gameProcessor::Matrix3X3::GetTranslate(mTranslate);

			gameProcessor::hRectangle renderRectangle = mRectangle;
			renderRectangle.SetTopLeft(renderRectangle.GetTopLeft() - gameProcessor::Vector2(mElapsedDistance, 0));
			renderRectangle.SetBottomLeft(renderRectangle.GetBottomLeft() - gameProcessor::Vector2(mElapsedDistance, 0));
			//renderRectangle.SetTopRight(renderRectangle.GetTopRight() * translateMatrix);
			//renderRectangle.SetBottomRight(renderRectangle.GetBottomRight() * translateMatrix);
			mAnimationInstnace->Render(renderManager, renderRectangle, nonTranslateMatrix);

			renderManager->FillCircle(mCollider, mTransform * compositeTrasform, gameProcessor::Helper::GetRGBA(255, 0, 255, 50));
			renderManager->DrawCircle(mCollider, mTransform * compositeTrasform, gameProcessor::Helper::GetRGBA(255, 0, 255, 255));
		}

		for (Object* child : mChildren)
		{
			child->Render(renderManager, compositeTrasform);
		}
	}
}