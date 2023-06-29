#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <d2d1helper.h>
#include <vector>

#include "GameProcessor.h"
#include "TimeManger.h"
#include "RenderManger.h"
#include "InputManager.h"
#include "TimeManger.h"
#include "RenderManger.h"
#include "hRectangle.h"
#include "Camara.h"

namespace camara
{
	class D2DCamara : public gameProcessor::GameProcessor
	{
	public:
		D2DCamara(UINT width, UINT height, std::wstring name);
		virtual ~D2DCamara() = default;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		gameProcessor::TimeManager mTimeManager;
		gameProcessor::RenderManager mRenderManager;
		gameProcessor::InputManager mInputManager;

		std::vector<gameProcessor::hRectangle> mObjects;
		Camara mCamara;
	};
}