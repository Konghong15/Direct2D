#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <d2d1helper.h>
#include <vector>

#include "GameProcessor.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "hRectangle.h"
#include "Circle.h"

namespace gameProcessor
{
	class Object;
}

namespace project2
{
	enum class eActivateShapeType
	{
		Rectangle,
		Circle
	};

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

		eActivateShapeType mCurrentShapeType;
		gameProcessor::hRectangle mRectangleUI;
		gameProcessor::Circle mCircleUI;

		std::vector<gameProcessor::hRectangle> mRectagles;
		std::vector<gameProcessor::Circle> mCircles;
	};
}