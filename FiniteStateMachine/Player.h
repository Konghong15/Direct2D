#pragma once

#include "Object.h"
#include "ePlayerState.h"

namespace gameProcessor
{
	class InputManager;
	class AnimationInstance;
}

namespace finiteStateMachine
{
	class Weapon;
	class PlayerState;

	class Player : public Object
	{
		friend class PlayerState;
		friend class PlayerIdle;
		friend class PlayerMove;
		friend class PlayerDeath;

	public:
		Player(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float colliderArea, Weapon* weapon, float speed);
		~Player();

		void HandleInput(gameProcessor::InputManager* inputManager);
		void OnCollision();

		virtual void Update(float deltaTime) override;
		virtual void Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& compositeTrasform) override;

		inline void SetAttackDirection(const gameProcessor::Vector2& attackDirection);
		inline const gameProcessor::Vector2& GetAttackDirection() const;

	private:
		enum { MAX_ACCELERATION = 200 };

		gameProcessor::AnimationInstance* mAnimationInstnace;

		gameProcessor::Vector2 mVelocity;
		gameProcessor::Vector2 mDirection;
		float mSpeed;
		float mAcceleration;
		const float mAccelerationIncrement = 400;
		const float mMaxAcceleration = 100;

		gameProcessor::Vector2 mAttackDirection;
		ePlayerState mPlayerState;
		Weapon* mWeapon;

		bool mbIsLeft;
		bool mbIsAttack;


		PlayerState* mStates[static_cast<unsigned int>(ePlayerState::Size)];
		PlayerState* mCurrentState;

		// 1. 이벤트 기반 구조 관련 서적 : 
		// 2. 아까 가이드 주신 펑터나 람다로 짠 FSM 예시코드
	};

	void Player::SetAttackDirection(const gameProcessor::Vector2& attackDirection)
	{
		mAttackDirection = attackDirection;
	}

	const gameProcessor::Vector2& Player::GetAttackDirection() const
	{
		return mAttackDirection;
	}
}