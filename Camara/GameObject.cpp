#include <stdlib.h>

#include "GameObject.h"
#include "RenderManger.h"


gameProcessor::hRectangle mRectangle;

gameProcessor::Matrix3X3 mTransform;
gameProcessor::Vector2 mTranslate;
gameProcessor::Vector2 mDirection;
float mScale;

float mSpeed;

namespace camara
{
	GameObject::GameObject(const gameProcessor::hRectangle& rectangle, float speed)
		: mRectangle(rectangle)
		, mSpeed(speed)
		, mScale(1.f)
		, mDirection(rand(), rand())
		, mTranslate(rectangle.GetCenter())
		, mTransform(gameProcessor::Matrix3X3::Identity())
	{
		mDirection.Normalize();

		mRectangle.Move(-mTranslate.GetX(), -mTranslate.GetY());
	}

	void GameObject::Update(float deltaTime)
	{
		mTranslate.Move(mSpeed * deltaTime * mDirection.GetX(), mSpeed * deltaTime * mDirection.GetY());

		mTransform = gameProcessor::Matrix3X3::ComineMatrix(3
			, gameProcessor::Matrix3X3::GetScale(mScale, mScale)
			, gameProcessor::Matrix3X3::GetRotate(mDirection.GetX(), mDirection.GetY())
			, gameProcessor::Matrix3X3::GetTranslate(mTranslate));
	}

	void GameObject::Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& transform, D2D1_COLOR_F color)
	{
		renderManager->DrawRectangle(mRectangle, mTransform * transform, color);
		color.a = 0.5f;
		renderManager->FillRectangle(mRectangle, mTransform * transform, color);
	}
}