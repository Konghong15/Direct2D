#include "Object.h"
#include "RenderManger.h"

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

	void Object::Render(RenderManager* renderer)
	{
		renderer->DrawBitMap(mWorldRectangle, mAnimationInstance);
	}
}