#include <cassert>

#include "AnimationInstance.h"
#include "Player.h"
#include "InputManager.h"
#include "Weapon.h"

namespace finiteStateMachine
{
	Player::Player(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, Weapon* weapon, float speed)
		: Object(rectangle)
		, mAnimationInstnace(animationInstance)
		, mSpeed(speed)
		, mPlayerState(ePlayerState::Idle)
		, mWeapon(weapon)
		, mAttackDirection(-1, 0)
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
		case ePlayerState::Attack:
		{
			// haha
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
				mDirection.Move(0, 1);
			}
			if (inputManager->GetKeyState(VK_DOWN) == gameProcessor::eKeyState::Hold)
			{
				mDirection.Move(0, -1);
			}
			if (inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::Hold)
			{
				mDirection.Move(-1, 0);
			}
			if (inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::Hold)
			{
				mDirection.Move(1, 0);
			}

			mDirection.Normalize();
		}
		break;
		default:
			assert(false);
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

		for (Object* child : mChildren)
		{
			child->Update(deltaTime);
		}
	}

	void Player::Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& compositeTrasform)
	{
		mAnimationInstnace->Render(renderManager, mRectangle, gameProcessor::Matrix3X3::ComineMatrix(3, gameProcessor::Matrix3X3::GetScale(mDirection.GetX() <= 0 ? 1 : -1, -1), mTransform, compositeTrasform));

		for (Object* child : mChildren)
		{
			child->Render(renderManager, compositeTrasform);
		}
	}
}