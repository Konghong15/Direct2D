#include <cassert>

#include "BaseFiniteStateMachine.h"
#include "BaseState.h"

namespace finiteStateMachine
{
	void BaseFiniteStateMachine::Update(Object* object, float deltaTime)
	{
		mCurrentState->Update(object, deltaTime);
		std::string nextState = mCurrentState->UpdateState(object);

		if (nextState != mCurrentState->GetStateName())
		{
			mCurrentState->Exit(object);

			auto iter = mStateMap.find(nextState);
			assert(iter != mStateMap.end());
			mCurrentState = iter->second;

			mCurrentState->Exit(object);
		}
	}
}