#pragma once

#include "hRectangle.h"
#include "AnimationInstance.h"

namespace gameProcessor
{
	class RenderManager;

	class Object
	{
	public:
		Object(hRectangle worldRectangle, AnimationInstance animationInstace);
		~Object() = default;

		void Update(float deltaTime);
		void Render(RenderManager* renderer);

	private:
		hRectangle mWorldRectangle;
		AnimationInstance mAnimationInstance;
	};
}