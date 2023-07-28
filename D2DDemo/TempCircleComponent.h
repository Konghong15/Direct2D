#pragma once

#include "Component.h"
#include "IUpdateable.h"

namespace d2dFramework
{
	class GameObject;
}

namespace d2dDemo
{
	class TempCircleComponent
		: public d2dFramework::Component
		, public d2dFramework::IUpdateable
	{
	public:
		TempCircleComponent(d2dFramework::GameObject* owner);
		virtual ~TempCircleComponent() = default;

		virtual void Update(float deltaTime);
	};
}