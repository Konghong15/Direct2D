#pragma once

namespace gameProcessor
{
	class InputManager;
}

namespace entityCamara
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