#pragma once

#include "Object.h"

namespace gameProcessor
{
	class InputManager;
	class AnimationInstance;
}

namespace finiteStateMachine
{
	enum class ePlayerState
	{
		Idle,
		Move,
		Death
	};

	class Weapon;

	class Player : public Object
	{
	public:
		Player(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float colliderArea, Weapon* weapon, float speed);
		~Player();

		void HandleInput(gameProcessor::InputManager* inputManager);
		virtual void Update(float deltaTime) override;
		virtual void Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& compositeTrasform) override;

		inline void SetAttackDirection(const gameProcessor::Vector2& attackDirection);
		inline const gameProcessor::Vector2& GetAttackDirection() const;

	private:
		gameProcessor::AnimationInstance* mAnimationInstnace;
		float mSpeed;

		gameProcessor::Vector2 mAttackDirection;
		ePlayerState mPlayerState;
		Weapon* mWeapon;

		bool mbIsLeft;
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