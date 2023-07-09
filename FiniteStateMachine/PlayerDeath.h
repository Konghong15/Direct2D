#pragma once

#include "PlayerState.h"

namespace finiteStateMachine
{
	class PlayerDeath : public PlayerState
	{
	public:
		PlayerDeath();
		virtual ~PlayerDeath() = default;

		virtual void HandleInput(gameProcessor::InputManager* inputManager) override;
		virtual ePlayerState HandleState(Player* player) override;
		virtual void Enter(Player* player) override;
		virtual void Update(Player* player, float deltaTime) override;

	private:
		const float mDeathMoveSpeed;
		bool mbIsDrop;
	};
}