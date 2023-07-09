#pragma once

#include "Object.h"
#include "Circle.h"

namespace gameProcessor
{
	class InputManager;
	class AnimationInstance;
}

namespace finiteStateMachine
{
	enum class eEnemyState
	{
		Idle,
		Discover,
		Trace,
		Attack,
		Death
	};

	class Weapon;
	class Player;
	class IMovealbe;

	class Enemy : public Object
	{
	public:
		Enemy(gameProcessor::AnimationInstance* animationInstance, const gameProcessor::hRectangle& rectangle, float colliderArea, Weapon* weapon, float speed, float patrallDistance, float attackDistance);
		~Enemy();

		virtual void HandleState(void);
		virtual void Update(float deltaTime) override;
		virtual void Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& compositeTrasform) override;

		inline void SetPlayer(Player* player);

	private:
		void changeState(eEnemyState state);

	private:
		gameProcessor::AnimationInstance* mAnimationInstnace;
		gameProcessor::Circle mPatrallArea;
		gameProcessor::Circle mAttackArea;

		float mSpeed;

		eEnemyState mEnemiesState;
		Player* mPlayer;
		Weapon* mWeapon;

		bool mbPatrall;
		bool mbAttack;
		bool mbIsProgressAttack;
	};

	void Enemy::SetPlayer(Player* player)
	{
		mPlayer = player;
	}
}