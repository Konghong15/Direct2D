#pragma once

#include <map>
#include <string>

namespace finiteStateMachine
{
	class BaseState;
	class Object;

	class BaseFiniteStateMachine
	{
	public:
		BaseFiniteStateMachine() = default;
		virtual ~BaseFiniteStateMachine() = 0 {}

		virtual void Update(Object* object, float deltaTime);

	private:
		std::map<std::string, BaseState*> mStateMap;
		BaseState* mCurrentState;
	};
}