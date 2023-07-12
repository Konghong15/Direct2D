#pragma once

#include "PlayerState.h"
#include "hRectangle.h"

namespace finiteStateMachine
{
	class PlayerIdle : public PlayerState
	{
	public:
		PlayerIdle();
		virtual ~PlayerIdle() = default;

		virtual void OnHandleEvent(Player* player, const std::string& event, const std::string& data);
		virtual ePlayerState UpdateState(Player* player);

		virtual void Enter(Player* player) override;
		virtual void Update(Player* player, float deltaTime) override;
	};
}