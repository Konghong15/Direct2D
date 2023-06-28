#pragma once

#include "ShapeObject.h"
#include "Circle.h"

namespace project2
{
	class  CircleObject final : public ShapeObject
	{
	public:
		CircleObject(const gameProcessor::Circle& circle);
		~CircleObject() = default;

		void Update(gameProcessor::InputManager* inputManager, float deltaTime) override;
		void Render(gameProcessor::RenderManager* renderManager) override;

	private:
		gameProcessor::Circle mCircle;

		gameProcessor::Matrix3X3 mScale;
		gameProcessor::Matrix3X3 mRotate;
		gameProcessor::Matrix3X3 mTranslate;
		gameProcessor::Matrix3X3 mTransform;
	};
}