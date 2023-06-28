#pragma once

#include "ShapeObject.h"
#include "hRectangle.h"

namespace project2
{
	class RectangleObject final : public ShapeObject
	{
	public:
		RectangleObject(const gameProcessor::hRectangle& rectangle, float radian = 0.f);
		~RectangleObject() = default;

		void Update(gameProcessor::InputManager* inputManager, float deltaTime) override;
		void Render(gameProcessor::RenderManager* renderManager) override;

	private:
		gameProcessor::hRectangle mRectangle;
		float mRadian;

		gameProcessor::Matrix3X3 mScale;
		gameProcessor::Matrix3X3 mRotate;
		gameProcessor::Matrix3X3 mTranslate;
		gameProcessor::Matrix3X3 mTransform;
	};
}