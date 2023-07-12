#pragma once

namespace gameProcessor
{
	class InputManager;
}

namespace finiteStateMachine
{

	class IInputHandleable
	{
	public:
		virtual void HandleInput(gameProcessor::InputManager* inputManager) = 0;
	};
}