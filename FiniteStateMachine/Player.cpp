#include <cassert>

#include "AnimationInstance.h"
#include "Player.h"
#include "InputManager.h"
#include "Weapon.h"
#include "RenderManger.h"
#include "Helper.h"

namespace finiteStateMachine
{
	Player::Player(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float colliderArea, Weapon* weapon, float speed)
		: Object(rectangle, colliderArea)
		, mAnimationInstnace(animationInstance)
		, mSpeed(speed)
		, mPlayerState(ePlayerState::Idle)
		, mWeapon(weapon)
		, mAttackDirection(-1, 0)
		, mbIsLeft(true)
	{
	}

	Player::~Player()
	{
		delete mAnimationInstnace;
	}

	void Player::HandleInput(gameProcessor::InputManager* inputManager)
	{
		switch (mPlayerState)
		{
		case ePlayerState::Idle:
		{
			if (inputManager->GetKeyState('X') == gameProcessor::eKeyState::Push)
			{
				mWeapon->Action(mAttackDirection);
			}

			if (inputManager->GetKeyState(VK_UP) == gameProcessor::eKeyState::Push
				|| inputManager->GetKeyState(VK_DOWN) == gameProcessor::eKeyState::Push
				|| inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::Push
				|| inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::Push)
			{
				mPlayerState = ePlayerState::Move;
				mAnimationInstnace->SetAnimationIndex(1);

				return;
			}
		}
		break;
		case ePlayerState::Move:
		{
			if (inputManager->GetKeyState('X') == gameProcessor::eKeyState::Push)
			{
				mWeapon->Action(mAttackDirection);
			}

			if (inputManager->GetKeyState(VK_UP) == gameProcessor::eKeyState::None
				&& inputManager->GetKeyState(VK_DOWN) == gameProcessor::eKeyState::None
				&& inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::None
				&& inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::None)
			{
				mPlayerState = ePlayerState::Idle;
				mAnimationInstnace->SetAnimationIndex(0);

				return;
			}

			if (inputManager->GetKeyState(VK_UP) == gameProcessor::eKeyState::Hold)
			{
				mDirection.SetY(1);
			}
			else if (inputManager->GetKeyState(VK_DOWN) == gameProcessor::eKeyState::Hold)
			{
				mDirection.SetY(-1);
			}
			else
			{
				mDirection.SetY(0);
			}
			if (inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::Hold)
			{
				mbIsLeft = true;
				mDirection.SetX(-1);
			}
			else if (inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::Hold)
			{
				mbIsLeft = false;
				mDirection.SetX(1);
			}
			else
			{
				mDirection.SetX(0);
			}

			mDirection.Normalize();
		}
		break;
		case ePlayerState::Death:
		{
			if (mAnimationInstnace->GetFrameIndex() < mAnimationInstnace->GetTotalFrameCount() / 2)
			{
				mDirection.SetXY(0, 1.f);
			}
			else
			{
				mDirection.SetXY(0, -1.f);
			}

			if (mAnimationInstnace->GetIsEnd())
			{
				mPlayerState = ePlayerState::Idle;
				mAnimationInstnace->SetAnimationIndex(static_cast<int>(ePlayerState::Idle));
				mAnimationInstnace->InitIsEnd();
				mAnimationInstnace->SetFrameIndex(0);

				int area = 500;
				mTranslate.Move(rand() % area - area / 2, rand() % area - area / 2);
				mbIsAlive = true;
			}
		}
		break;
		default:
			assert(false);
		}

		if (mPlayerState != ePlayerState::Death && !mbIsAlive)
		{
			mPlayerState = ePlayerState::Death;
			mAnimationInstnace->SetAnimationIndex(static_cast<int>(ePlayerState::Death));
			mAnimationInstnace->InitIsEnd();
			mAnimationInstnace->SetFrameIndex(0);
		}

		mWeapon->HandleState();
	}

	void Player::Update(float deltaTime)
	{
		if (mPlayerState == ePlayerState::Move)
		{
			mTranslate.Move(mDirection.GetX() * mSpeed * deltaTime, mDirection.GetY() * mSpeed * deltaTime);
		}
		mAnimationInstnace->Update(deltaTime);
		mTransform = combineMatrix();

		if (mPlayerState == ePlayerState::Death)
		{
			mTranslate.Move(mDirection.GetX() * 20 * deltaTime, mDirection.GetY() * 20 * deltaTime);
		}

		for (Object* child : mChildren)
		{
			child->Update(deltaTime);
		}
	}

	void Player::Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& compositeTrasform)
	{
		mAnimationInstnace->Render(renderManager, mRectangle, gameProcessor::Matrix3X3::ComineMatrix(3, gameProcessor::Matrix3X3::GetScale(mbIsLeft ? 1 : -1, -1), mTransform, compositeTrasform));
		renderManager->FillCircle(mCollider, mTransform * compositeTrasform, gameProcessor::Helper::GetRGBA(0, 255, 0, 50));
		renderManager->DrawCircle(mCollider, mTransform * compositeTrasform, gameProcessor::Helper::GetRGBA(0, 255, 0, 255));

		for (Object* child : mChildren)
		{
			child->Render(renderManager, compositeTrasform);
		}
	}
}