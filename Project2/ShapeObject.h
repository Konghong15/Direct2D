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
		inline virtual void updateMatrix();
		inline void toggleSelect();

	protected:
		bool mbHover;
		bool mbSelect;
		gameProcessor::Matrix3X3 mScale;
		gameProcessor::Matrix3X3 mRotate;
		gameProcessor::Matrix3X3 mTranslate;
		gameProcessor::Matrix3X3 mTransform;
	};

	void ShapeObject::updateMatrix()
	{
		mTransform = gameProcessor::Matrix3X3::ComineMatrix(3, mScale, mRotate, mTranslate);
	}

	void ShapeObject::toggleSelect()
	{
		mbSelect ^= true;
	}
}