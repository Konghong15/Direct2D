#include <stdlib.h>

#include "GameObject.h"
#include "RenderManger.h"

namespace camara
{
	GameObject::GameObject(const gameProcessor::hRectangle& rectangle, float speed)
		: mRectangle(rectangle)
		, mSpeed(speed)
		, mDirection(rand(), rand())
	{
		mDirection.Normalize();
	}

	void GameObject::Update(float deltaTime)
	{
		mRectangle.Move(mDirection.GetX() * mSpeed * deltaTime, mDirection.GetY() * mSpeed * deltaTime);
	}

	void GameObject::Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& transform, D2D1_COLOR_F color)
	{
		renderManager->DrawRectangle(mRectangle, transform, color);
	}
}