#include "FiniteStateMachine.h"
#include "FiniteState.h"

namespace finiteStateMachine
{
	FiniteStateMachine::FiniteStateMachine(Player* onwerPlayer)
		: mOnwerPlayer(onwerPlayer)
		, mCurrentState(nullptr)
	{
	}

	FiniteStateMachine::~FiniteStateMachine()
	{
		for (auto iter = mStates.begin(); iter != mStates.end(); ++iter)
		{
			delete iter->second;
		}
	}

	void FiniteStateMachine::Update()
	{
		assert(mCurrentState != nullptr);
		mCurrentState->Update();
	}

	void FiniteStateMachine::RegisterState(FiniteState* state)
	{
		mStates.insert({ state->GetStateName(), state });
		state->SetFiniteStateMachine(this);
	}
}