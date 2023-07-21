#include "GameObject.h"

namespace gameProcessor
{
	GameObject::GameObject(const hRectangle& rectangle)
		: GameObject(rectangle, { { 1, 1 }, 0, {0, 0} })
	{
	}

	GameObject::GameObject(const hRectangle& rectangle, TransformInfo transformInfo)
		: mLocalRectangle(rectangle)
		, mTransformInfo(
			transformInfo.Scale,
			transformInfo.RotateInRadian,
			{
				transformInfo.Translate.GetX() + rectangle.GetCenter().GetX() / 2.0f,
				transformInfo.Translate.GetY() + rectangle.GetCenter().GetY() / 2.0f
			})
		, mParent(nullptr)
	{
		mLocalRectangle.Move(-rectangle.GetCenter().GetX() / 2.0f, -rectangle.GetCenter().GetY() / 2.0f);
		updateWorldTransform();
		updateWorldRectangle();
	}
}
