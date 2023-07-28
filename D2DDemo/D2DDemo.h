#pragma once

#include "GameProcessor.h"

namespace d2dFramework
{
	class GameObject;
}

namespace d2dDemo
{

	class D2DDemo : public d2dFramework::GameProcessor
	{
	public:
		D2DDemo(UINT width, UINT height, std::wstring name);
		virtual ~D2DDemo() = default;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Destroy() override;

	private:
		d2dFramework::GameObject* mGameObject0;
		d2dFramework::GameObject* mGameObject1;
		d2dFramework::GameObject* mCircle;
	};
}