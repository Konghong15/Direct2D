#pragma once

namespace gameProcessor
{
	class InputManager;
}

namespace entityComponentSystem
{
	class InputComponent
	{
	public:
		InputComponent(unsigned int entityId);
		virtual ~InputComponent() = default;

		void Update(gameProcessor::InputManager* inputManager);

	private:
	};
}