#pragma once

#include "hRectangle.h"
#include "Matrix3X3.h"

namespace gameProcessor
{
	class InputManager;
}

namespace componentBased
{
	class OldTransformComponent
	{
	public:
		OldTransformComponent(const gameProcessor::Vector2& scale, float rotateInRadian, const gameProcessor::Vector2& translate);

		void Update(gameProcessor::InputManager* inputManager, float deltaTime);
		inline const gameProcessor::Matrix3X3& GetTransform() const;

	private:
		gameProcessor::Vector2 mScale;
		float mRotateInRadian;
		gameProcessor::Vector2 mTranslate;
		gameProcessor::Matrix3X3 mTransform;
	};

	const gameProcessor::Matrix3X3& OldTransformComponent::GetTransform() const
	{
		return mTransform;
	}
}