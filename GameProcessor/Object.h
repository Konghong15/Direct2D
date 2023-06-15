#pragma once

#include "hRectangle.h"
#include "AnimationInstance.h"

namespace gameProcessor
{
	class Renderer;

	class Object
	{
	public:
		Object(hRectangle worldRectangle, AnimationInstance animationInstace);
		~Object() = default;

		void Update(float deltaTime);
		void Render(Renderer* renderer);

	private:
		hRectangle mWorldRectangle;
		AnimationInstance mAnimationInstance;
	};
}