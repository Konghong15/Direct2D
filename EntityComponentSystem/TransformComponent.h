#pragma once

#include "Vector2.h"
#include "Matrix3X3.h"
#include "Component.h"

namespace entityComponentSystem
{
	struct TransformComponent : public Component
	{
		TransformComponent(const gameProcessor::Vector2& scale, float rotateInRadian, const gameProcessor::Vector2& translate)
			: Component(eComponentType::Transform)
			, Scale(scale)
			, RotateInRadian(rotateInRadian)
			, Translate(translate)
			, Transform(gameProcessor::Matrix3X3::Identity())
		{
		}

		gameProcessor::Vector2 Scale;
		float RotateInRadian;
		gameProcessor::Vector2 Translate;
		gameProcessor::Matrix3X3 Transform;
	};
}