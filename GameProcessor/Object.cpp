#include "Object.h"
#include "Renderer.h"

namespace gameProcessor
{
	Object::Object(hRectangle worldRectangle, AnimationInstance animationInstace)
		: mWorldRectangle(worldRectangle)
		, mAnimationInstance(animationInstace)
	{
	}

	void Object::Update(float deltaTime)
	{
		mAnimationInstance.Update(deltaTime);
	}

	void Object::Render(Renderer* renderer)
	{
		renderer->DrawBitMap(mWorldRectangle, mAnimationInstance);
	}
}