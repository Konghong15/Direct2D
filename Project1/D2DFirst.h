#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <d2d1helper.h>

#include "GameProcessor.h"
#include "Timer.h"
#include "Renderer.h"

namespace gameProcessor
{
	class Object;
}

namespace project1
{
	class D2DFirst : public gameProcessor::GameProcessor
	{
	public:
		D2DFirst(UINT width, UINT height, std::wstring name);
		virtual ~D2DFirst() = default;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		gameProcessor::Timer mTimer;
		gameProcessor::Renderer mRenderer;

		gameProcessor::Object* mBackground;
		gameProcessor::Object* mPlayers[10][10];
	};
}