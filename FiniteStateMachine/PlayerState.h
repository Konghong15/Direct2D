#pragma once

#include "ePlayerState.h"
#include "IInputHandleable.h"

namespace finiteStateMachine
{
	class Player;

	class PlayerState : public IInputHandleable
	{
	public:
		PlayerState(ePlayerState state);
		virtual ~PlayerState() = default;

		virtual void HandleInput(gameProcessor::InputManager* inputManager) = 0;
		virtual ePlayerState HandleState(Player* player) = 0; // 현재 상태와 다른 상태를 반환할 시 변경
		virtual void Enter(Player* player);
		virtual void Update(Player* player, float deltaTime);
		virtual void Exit(Player* player);

		inline ePlayerState GetState() const;

	protected:
		inline void SetNextState(ePlayerState state);
		inline ePlayerState GetNextState() const;

	private:
		ePlayerState mState;
		ePlayerState mNextState;
	};

	ePlayerState PlayerState::GetState() const
	{
		return mState;
	}

	void PlayerState::SetNextState(ePlayerState state)
	{
		mNextState = state;
	}

	ePlayerState PlayerState::GetNextState() const
	{
		return mNextState;
	}
}