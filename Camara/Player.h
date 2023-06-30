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
		virtual void Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& transform, D2D1_COLOR_F color);
	};
}