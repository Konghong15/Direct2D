#pragma once

#include "Matrix3X3.h"
#include "hRectangle.h"
#include "InputManager.h"

namespace camara
{
	class Camara
	{
	public:
		Camara(unsigned int width, unsigned int height, float speed);
		~Camara() = default;

		void Update(gameProcessor::InputManager* inputManager, float deltaTime);

		inline const gameProcessor::Matrix3X3& GetTransform() const;
		inline const gameProcessor::hRectangle& GetClippingRectangle() const;

	private:
		const gameProcessor::hRectangle mRectangle;
		const gameProcessor::Matrix3X3 mOrginTranslate;
		gameProcessor::Matrix3X3 mTransform;

		gameProcessor::Vector2 mTranslate;
		gameProcessor::Vector2 mDirection;
		float mScale;
		float mRotateInRadian;

		float mSpeed;
	};

	const gameProcessor::Matrix3X3& Camara::GetTransform() const
	{
		return mTransform;
	}

	const gameProcessor::hRectangle& Camara::GetClippingRectangle() const
	{
		return mRectangle * mTransform;
	}
}