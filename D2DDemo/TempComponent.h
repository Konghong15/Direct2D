#pragma once

#include "Component.h"
#include "IUpdateable.h"

namespace d2dFramework
{
	class GameObject;
}

namespace d2dDemo
{
	class TempComponent
		: public d2dFramework::Component
		, public d2dFramework::IUpdateable
	{
	public:
		TempComponent(d2dFramework::GameObject* owner);
		virtual ~TempComponent() = default;

		virtual void Update(float deltaTime);
	};
}