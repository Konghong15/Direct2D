#pragma once

#include "Object.h"
#include "Circle.h"
#include "eEnemyState.h"

namespace gameProcessor
{
	class InputManager;
	class AnimationInstance;
}

namespace finiteStateMachine
{
	class Weapon;
	class Player;
	class EnemyState;

	class Enemy : public Object
	{
		friend class EnemyState;
		friend class EnemyIdle;
		friend class EnemyDiscover;
		friend class EnemyTrace;
		friend class EnemyAttack;
		friend class EnemyDeath;

	public:
		Enemy(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float colliderArea, Weapon* weapon, float speed, float patrallDistance, float attackDistance);
		~Enemy();

		virtual void Update(float deltaTime) override;
		virtual void Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& compositeTrasform) override;

		inline void SetPlayer(Player* player);

	private:
		gameProcessor::AnimationInstance* mAnimationInstnace;
		gameProcessor::Circle mPatrallArea;
		gameProcessor::Circle mAttackArea;

		float mSpeed;

		Player* mPlayer;
		Weapon* mWeapon;

		bool mbPatrall;
		bool mbAttack;
		bool mbIsProgressAttack;

		EnemyState* mStates[static_cast<unsigned int>(eEnemyState::Size)];
		EnemyState* mCurrentState;
	};

	void Enemy::SetPlayer(Player* player)
	{
		mPlayer = player;
	}
}