#pragma once

#include <string>

namespace finiteStateMachine
{
	class Object;

	class BaseState
	{
	public:
		BaseState(const std::string& stateName) : mStateName(stateName) {}
		virtual ~BaseState() = 0 {};

		virtual void OnHandleEvent(Object* object, const std::string& event, const std::string& data) = 0;
		virtual void Enter(Object* object) = 0;
		virtual std::string UpdateState(Object* object) = 0;
		virtual void Update(Object* object, float deltaTime) = 0;
		virtual void Exit(Object* object) = 0;

		inline const std::string& GetStateName() const;

	private:
		const std::string mStateName;
	};

	const std::string& BaseState::GetStateName() const
	{
		return mStateName;
	}
}