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

		virtual void OnHandleEvent(Player* player, const std::string& event, const std::string& data);
		virtual ePlayerState UpdateState(Player* player);

		virtual void Enter(Player* player) override;
		virtual void Update(Player* player, float deltaTime) override;
		virtual void Exit(Player* player);

	private:
		bool mbIsInput;
	};
}