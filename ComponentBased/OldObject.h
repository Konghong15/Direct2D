#pragma once

#include "hRectangle.h"
#include "Matrix3X3.h"

namespace gameProcessor
{
	class RenderManager;
	class InputManager;
}

namespace componentBased
{
	class OldObject final
	{
	public:
		OldObject(const gameProcessor::Vector2& scale, float rotateInRadian, const gameProcessor::Vector2& translate, const gameProcessor::Vector2& direction, float speed, float accelerationIncrement, float maxAcceleration, const gameProcessor::hRectangle& rectangle);
		~OldObject() = default;

		void Update(gameProcessor::InputManager* inputManager, float deltaTime);
		void Render(gameProcessor::RenderManager* renderManager);

	private:
		// trasform info
		gameProcessor::Vector2 mScale;
		float mRotateInRadian;
		gameProcessor::Vector2 mTranslate;
		gameProcessor::Matrix3X3 mTransform;

		// movement info
		gameProcessor::Vector2 mDirection;
		float mSpeed;
		float mAcceleration;
		const float mAccelerationIncrement;
		const float mMaxAcceleration;

		// rendering info
		gameProcessor::hRectangle mRectangle;
		// + bitmap, animation efc
	};
}