#include "Object.h"
#include "RenderManger.h"

namespace finiteStateMachine
{
	Object::Object(const gameProcessor::hRectangle& rectangle, float colliderArea, Object* parent)
		: mParent(parent)
		, mRectangle(rectangle)
		, mScale(1.f, 1.f)
		, mRotateInRadian(0.f)
		, mTranslate(mRectangle.GetCenter())
		, mTransform(combineMatrix())
		, mDirection(-1, 0)
		, mbIsAlive(true)
		, mCollider({0,0}, colliderArea)
	{
		mRectangle.Move(-mTranslate.GetX(), -mTranslate.GetY());
	}

	Object::~Object()
	{
		for (Object* child : mChildren)
		{
			delete child;
		}
	}

	void Object::Render(gameProcessor::RenderManager* renderManager, const gameProcessor::Matrix3X3& compositeTrasform)
	{
		renderManager->DrawRectangle(mRectangle, mTransform * compositeTrasform);

		for (Object* child : mChildren)
		{
			child->Render(renderManager, compositeTrasform);
		}
	}
}