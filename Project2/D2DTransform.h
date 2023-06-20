#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <d2d1helper.h>
#include <vector>
#include <memory>

#include "GameProcessor.h"
#include "TimeManger.h"
#include "RenderManger.h"
#include "InputManager.h"
#include "hRectangle.h"
#include "ShapeObject.h"

namespace gameProcessor
{
	class Object;
}

namespace project2
{
	class D2DTransform : public gameProcessor::GameProcessor
	{
	public:
		D2DTransform(UINT width, UINT height, std::wstring name);
		virtual ~D2DTransform() = default;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		gameProcessor::TimeManager mTimer;
		gameProcessor::RenderManager mRenderer;
		gameProcessor::InputManager mInputManager;

		std::vector<std::unique_ptr<ShapeObject>> mShapeObjects;
	};
}