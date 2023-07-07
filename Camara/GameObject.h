#pragma once

#include <d2d1.h>

#include "Vector2.h"
#include "hRectangle.h"
#include "Matrix3X3.h"

namespace gameProcessor
{
	class RenderManager;
}

namespace camara
{
	class GameObject
	{
	public:
		GameObject(const gameProcessor::hRectangle& rectangle, float speed);
		virtual ~GameObject() = default;

		virtual void Update(float deltaTime);
		virtual void Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& transform, D2D1_COLOR_F color);

		inline gameProcessor::hRectangle GetWorldRectangle() const;
		inline const gameProcessor::hRectangle& GetRectangle() const;
		inline const gameProcessor::Vector2& GetDirection() const;

	protected:
		gameProcessor::hRectangle mRectangle; // 로컬

		float mScale;
		gameProcessor::Vector2 mDirection;
		gameProcessor::Vector2 mTranslate;
		gameProcessor::Matrix3X3 mTransform; // 월드가기위한 변환행렬

		float mSpeed;
	};

	gameProcessor::hRectangle GameObject::GetWorldRectangle() const
	{
		return mRectangle * mTransform;
	}

	const gameProcessor::hRectangle& GameObject::GetRectangle() const
	{
		return mRectangle;
	}

	const gameProcessor::Vector2& GameObject::GetDirection() const
	{
		return mDirection;
	}
}