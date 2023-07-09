#pragma once

#include "PlayerState.h"

namespace finiteStateMachine
{
	class PlayerIdle : public PlayerState
	{
	public:
		PlayerIdle();
		virtual ~PlayerIdle() = default;

		virtual void HandleInput(gameProcessor::InputManager* inputManager) override;
		virtual ePlayerState HandleState(Player* player) override;
		virtual void Enter(Player* player) override;
		virtual void Update(Player* player, float deltaTime) override;

	private:
		bool mbIsAttack;
	};
}