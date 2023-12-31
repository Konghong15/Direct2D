#include <cassert>
#include <comdef.h>
#include <d2d1helper.h>
#include <Windows.h>

#include "D2DTransform.h"
#include "WinApp.h"
#include "Object.h"
#include "ShapeObject.h"
#include "CircleObject.h"
#include "RectangleObject.h"
#include "Collision.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

namespace project2
{
	using namespace gameProcessor;

	D2DTransform::D2DTransform(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mTimer()
		, mRenderer()
	{
		mShapeObjects.reserve(128);
	}

	void D2DTransform::Init()
	{
		HRESULT hr;
		hr = CoInitialize(NULL);
		assert(SUCCEEDED(hr));

		mRenderer.Init();
		mTimer.Init();
		mInputManager.Init();
		//mRectagles.reserve(128);
		//mCircles.reserve(128);
	}

	void D2DTransform::Update()
	{
		mTimer.Update();
		mInputManager.Update();
		const float DELTA_TIME = mTimer.GetDeltaTime();
		const Vector2& mousePos = mInputManager.GetMousePos();

		if (mInputManager.GetKeyState('1') == eKeyState::Push)
		{
			hRectangle rectangle(mousePos.GetX() - 100, mousePos.GetY() - 100, mousePos.GetX() + 100, mousePos.GetY() + 100);
			std::unique_ptr<ShapeObject> obj = std::make_unique<RectangleObject>(rectangle);
			mShapeObjects.push_back(std::move(obj));
		}
		else if (mInputManager.GetKeyState('2') == eKeyState::Push)
		{
			std::unique_ptr<ShapeObject> obj = std::make_unique<CircleObject>(Circle({ mousePos.GetX(), mousePos.GetY() },
				100));
			mShapeObjects.push_back(std::move(obj));
		}
		else if (mInputManager.GetKeyState(VK_ESCAPE) == eKeyState::Push)
		{
			mShapeObjects.clear();
		}

		for (auto iter = mShapeObjects.begin(); iter != mShapeObjects.end(); ++iter)
		{
			(*iter)->Update(&mInputManager, DELTA_TIME);
		}
	}

	void D2DTransform::Render()
	{
		mRenderer.BeginDraw();

		for (auto iter = mShapeObjects.begin(); iter != mShapeObjects.end(); ++iter)
		{
			(*iter)->Render(&mRenderer);
		}

		mRenderer.EndDraw();
	}

	void D2DTransform::Destroy()
	{
		mShapeObjects.clear();
		mRenderer.Release();
		CoUninitialize();
	}
}

