#include "Transform.h"

namespace d2dFramework
{
	Transform::Transform(GameObject* owner)
		: Component(owner)
		, mScale(1.f, 1.f)
		, mRotateInDegree(0.f)
		, mTranslate(0.f, 0.f)
	{
	}
}