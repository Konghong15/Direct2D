#include "Camera.h"

namespace d2dFramework
{
	Camera::Camera(unsigned int id, GameObject* owner)
		: Component(id, owner)
		, mSize(100, 100)
		, mScale(1.f, 1.f)
		, mRotateInDegree(0.f)
		, mTranslate(0.f, 0.f)
	{
	}
}