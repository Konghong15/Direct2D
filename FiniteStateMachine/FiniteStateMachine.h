#pragma once

#include <cassert>
#include <map>
#include <string>

#include "INotifiable.h"

namespace finiteStateMachine
{
	class FiniteState;
	class Player;

	class FiniteStateMachine : public INotifiable
	{
	public:
		FiniteStateMachine(Player* onwerPlayer);
		virtual ~FiniteStateMachine();

		virtual void OnNotify(const std::wstring& notifyName, const std::wstring& infomation) = 0;

		void Update();
		void RegisterState(FiniteState* state);

		inline void SetCurrentState(std::string stateName);

	private:


		std::map<std::string, FiniteState*> mStates;
		FiniteState* mCurrentState;
		Player* mOnwerPlayer;
	};

	void FiniteStateMachine::SetCurrentState(std::string stateName)
	{
		auto iter = mStates.find(stateName);
		assert(iter != mStates.end());

		mCurrentState = (*iter).second;
	}
}