#pragma once

#include <vector>
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
		static std::vector<Object*> mObject;

	private:
		hRectangle mWorldRectangle;
		AnimationInstance mAnimationInstance;
	};
}