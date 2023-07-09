#pragma once

#include "PlayerState.h"
#include "Vector2.h"

namespace finiteStateMachine
{
	class PlayerMove : public PlayerState
	{
	public:
		PlayerMove();
		virtual ~PlayerMove() = default;

		virtual void HandleInput(gameProcessor::InputManager* inputManager) override;
		virtual ePlayerState HandleState(Player* player) override;
		virtual void Enter(Player* player) override;
		virtual void Update(Player* player, float deltaTime) override;

	private:
		bool mbIsAttack;
		gameProcessor::Vector2 mDirection;
		bool mbIsLeft;
	};
}