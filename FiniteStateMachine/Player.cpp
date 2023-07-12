#include <cassert>

#include "AnimationInstance.h"
#include "Player.h"
#include "InputManager.h"
#include "Weapon.h"
#include "RenderManger.h"
#include "Helper.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerDeath.h"

namespace finiteStateMachine
{
	Player::Player(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float colliderArea, Weapon* weapon, float speed)
		: Object(rectangle, colliderArea)
		, mAnimationInstnace(animationInstance)
		, mVelocity(0, 0)
		, mDirection(-1, 0)
		, mSpeed(speed)
		, mAcceleration(0)
		, mPlayerState(ePlayerState::Idle)
		, mWeapon(weapon)
		, mAttackDirection(-1, 0)
		, mbIsLeft(true)
		, mbIsAttack(false)
		, mStates{ new PlayerIdle(), new PlayerMove(), new PlayerDeath() }
		, mCurrentState(mStates[static_cast<unsigned int>(ePlayerState::Idle)])
	{
	}

	Player::~Player()
	{
		delete mAnimationInstnace;

		for (PlayerState* state : mStates)
		{
			delete state;
		}
	}

	void Player::HandleInput(gameProcessor::InputManager* inputManager)
	{
		if (inputManager->GetKeyState(VK_SPACE) == gameProcessor::eKeyState::Push)
		{
			mCurrentState->OnHandleEvent(this, "restart", "");
			return;
		}

		if (inputManager->GetKeyState(VK_UP) == gameProcessor::eKeyState::Hold)
		{
			mCurrentState->OnHandleEvent(this, "arrowKeyInput", "up");
		}
		else if (inputManager->GetKeyState(VK_DOWN) == gameProcessor::eKeyState::Hold)
		{
			mCurrentState->OnHandleEvent(this, "arrowKeyInput", "down");
		}
		if (inputManager->GetKeyState(VK_LEFT) == gameProcessor::eKeyState::Hold)
		{
			mCurrentState->OnHandleEvent(this, "arrowKeyInput", "left");
		}
		else if (inputManager->GetKeyState(VK_RIGHT) == gameProcessor::eKeyState::Hold)
		{
			mCurrentState->OnHandleEvent(this, "arrowKeyInput", "right");
		}

		if (inputManager->GetKeyState('X') == gameProcessor::eKeyState::Push)
		{
			mCurrentState->OnHandleEvent(this, "attack", "");
		}
	}

	void Player::OnCollision()
	{
		mCurrentState->OnHandleEvent(this, "collisionEnemy", "");
	}

	void Player::Update(float deltaTime)
	{
		mCurrentState->Update(this, deltaTime);
		ePlayerState nextState = mCurrentState->UpdateState(this);

		if (nextState != mCurrentState->GetState())
		{
			mCurrentState->Exit(this);
			mCurrentState = mStates[static_cast<unsigned int>(nextState)];
			mCurrentState->Enter(this);
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