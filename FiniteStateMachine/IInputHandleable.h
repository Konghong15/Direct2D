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
		IInputHandleable() = default;
		virtual ~IInputHandleable() = default;

		virtual void HandleInput(gameProcessor::InputManager* inputManager) = 0;
	};
}