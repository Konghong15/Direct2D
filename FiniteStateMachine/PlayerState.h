#pragma once

#include <string>

#include "ePlayerState.h"

namespace finiteStateMachine
{
	class Player;

	class PlayerState
	{
	public:
		PlayerState(ePlayerState state);
		virtual ~PlayerState() = default;

		virtual void OnHandleEvent(Player* player, const std::string& event, const std::string& data) = 0;

		virtual ePlayerState UpdateState(Player* player) = 0;
		virtual void Enter(Player* player);
		virtual void Update(Player* player, float deltaTime);
		virtual void Exit(Player* player);

		inline ePlayerState GetState() const;

	private:
		ePlayerState mState;
	};

	ePlayerState PlayerState::GetState() const
	{
		return mState;
	}
}