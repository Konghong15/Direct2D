#pragma once

#include "GameObject.h"

namespace gameProcessor
{
	class InputManager;
}

namespace camara
{
	class Player : public GameObject
	{
	public:
		Player(const gameProcessor::hRectangle& rectangle, float speed);
		virtual ~Player() = default;

		virtual void HandleInput(gameProcessor::InputManager* inputManager);
	};
}