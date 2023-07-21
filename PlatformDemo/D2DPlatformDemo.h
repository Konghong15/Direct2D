#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <d2d1helper.h>

#include "GameProcessor.h"
#include "TimeManger.h"
#include "RenderManger.h"
#include "Camara.h"
#include "Obstacle.h"

namespace platform
{
	class PlatformObject;

	class D2DPlatformDemo : public gameProcessor::GameProcessor
	{
	public:
		D2DPlatformDemo(UINT width, UINT height, std::wstring name);
		virtual ~D2DPlatformDemo() = default;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		gameProcessor::Camara mCamara;
		PlatformObject* mPlayer;
		Obstacle* mObstacle0;
		Obstacle* mObstacle1;
	};
}