#include <cassert>
#include <comdef.h>
#include <d2d1helper.h>
#include <Windows.h>

#include "D2DTransform.h"
#include "WinApp.h"
#include "Object.h"

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
	}

	void D2DTransform::Init()
	{
		HRESULT hr;
		hr = CoInitialize(NULL);
		assert(SUCCEEDED(hr));

		mRenderer.Init();
		mTimer.Init();
		mInputManager.Init();

		mRectagles.reserve(128);
		mCircles.reserve(128);
	}

	void D2DTransform::Update()
	{
		mTimer.Update();
		mInputManager.Update();
		const float DELTA_TIME = mTimer.GetDeltaTime();

		if (mInputManager.GetKeyState(VK_LBUTTON) == eKeyState::Push)
		{
			const POINT& mousePos =  mInputManager.GetMousePos();
			
		}
	}

	void D2DTransform::Render()
	{
		mRenderer.BeginDraw();
		mRenderer.EndDraw();
	}

	void D2DTransform::Destroy()
	{
		mRenderer.Release();
		CoUninitialize();
	}
}

