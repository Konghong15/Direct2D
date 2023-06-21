#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <d2d1helper.h>

#include "GameProcessor.h"
#include "TimeManger.h"
#include "RenderManger.h"
#include "GameObject.h"

namespace hierarchicalObject
{
	class D2DHierarchicalObject : public gameProcessor::GameProcessor
	{
	public:
		D2DHierarchicalObject(UINT width, UINT height, std::wstring name);
		virtual ~D2DHierarchicalObject() = default;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		gameProcessor::TimeManager mTimeManager;
		gameProcessor::RenderManager mRenderManager;
		GameObject* mGameObject1;
		GameObject* mGameObject2;
		GameObject* mGameObject3;
		GameObject* mGameObject4;
	};
}