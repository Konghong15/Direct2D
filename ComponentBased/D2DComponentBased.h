#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <d2d1helper.h>

#include "GameProcessor.h"
#include "TimeManger.h"
#include "RenderManger.h"

namespace componentBased
{
	class D2DComponentBased : public gameProcessor::GameProcessor
	{
	public:
		D2DComponentBased(UINT width, UINT height, std::wstring name);
		virtual ~D2DComponentBased() = default;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		gameProcessor::TimeManager mTimeManager;
		gameProcessor::RenderManager mRenderManager;
	};
}