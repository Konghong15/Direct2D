#pragma once

#include "PlayerState.h"

namespace finiteStateMachine
{
	class PlayerDeath : public PlayerState
	{
	public:
		PlayerDeath();
		virtual ~PlayerDeath() = default;

		virtual void OnHandleEvent(Player* player, const std::string& event, const std::string& data);
		virtual ePlayerState UpdateState(Player* player);

		virtual void Enter(Player* player) override;
		virtual void Update(Player* player, float deltaTime) override;
		virtual void Exit(Player* player);

	private:
		enum { DEATH_MOVE_SPEED = 50 };

		bool mbIsRestart;
		bool mbIsDrop;
	};
}