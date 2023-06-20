#pragma once

namespace gameProcessor
{
	class RenderManager;
	class InputManager;
	class Vector2;
}

#include "Matrix3X3.h"

namespace project2
{
	class ShapeObject
	{
	public:
		ShapeObject(const gameProcessor::Vector2& center);
		virtual ~ShapeObject() = default;

		virtual void Update(gameProcessor::InputManager* inputManager, float deltaTime);
		virtual void Render(gameProcessor::RenderManager* renderManager) = 0;

	protected:
		inline void toggleSelect();

	protected:
		bool mbHover;
		bool mbSelect;
		gameProcessor::Matrix3X3 mScale;
		gameProcessor::Matrix3X3 mTranslate;
	};

	void ShapeObject::toggleSelect()
	{
		mbSelect ^= true;
	}
}