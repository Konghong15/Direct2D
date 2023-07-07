#pragma once

#include <string>

namespace finiteStateMachine
{
	class FiniteStateMachine;
	class FiniteTransition;

	class FiniteState
	{
	public:
		FiniteState(std::string stateName)
			: mStateName(stateName)
			, mFiniteStateMachine(nullptr)
		{
		}
		virtual ~FiniteState() = 0;

		virtual void HandleState() = 0;
		virtual void Enter() = 0;
		virtual void Update() = 0;
		virtual void Exit() = 0;

		inline void SetFiniteStateMachine(FiniteStateMachine* finiteStateMachine);
		inline void AddTransition(FiniteTransition* transition);

		inline const std::string& GetStateName() const;
		
	private:
		FiniteStateMachine* mFiniteStateMachine;
		std::string mStateName;
		std::vector<FiniteTransition*> mTransition;
	};

	void FiniteState::AddTransition(FiniteTransition* transition)
	{
		mTransition.push_back(transition);
	}

	void FiniteState::SetFiniteStateMachine(FiniteStateMachine* finiteStateMachine)
	{
		mFiniteStateMachine = finiteStateMachine;
	}

	inline const std::string& FiniteState::GetStateName() const
	{
		return mStateName;
	}
}