#include <cassert>
#include <comdef.h>
#include <d2d1helper.h>

#include "D2DFirst.h"
#include "WinApp.h"
#include "Object.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

namespace project1
{
	using namespace gameProcessor;

	D2DFirst::D2DFirst(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mTimeManager()
		, mRenderManager()
		, mBackground(nullptr)
		, mPlayers{ nullptr, }
	{
	}

	void D2DFirst::Init()
	{
		HRESULT hr;
		hr = CoInitialize(NULL);
		assert(SUCCEEDED(hr));

		mRenderManager.Init();
		mTimeManager.Init();

		const WCHAR* runPath = L"./resource/run.png";
		const WCHAR* backgroundPath = L"./resource/midnight.png";

		mRenderManager.CreateD2DBitmapFromFile(runPath);
		mRenderManager.CreateD2DBitmapFromFile(backgroundPath);

		std::vector<std::vector<hRectangle>> frameAnimationInfo =
		{
			{
				{0.f, 0.f, 784.f, 320.f},
				{789.f, 0.f, 1573.f, 320.f},
				{0.f, 325.f, 784.f, 645.f},
				{789.f, 325.f, 1573.f, 645.f}
			}
		};

		mRenderManager.CreateAnimationAsset(backgroundPath, frameAnimationInfo);

		frameAnimationInfo =
		{
			{
				{ 28, 36, 131, 120},
				{ 148, 36, 234, 120 },
				{ 255, 34, 342, 120 },
				{ 363, 32, 439, 120 },
				{ 458, 31, 549, 120 },
				{ 567, 40, 670, 120 },
				{ 686, 32, 771, 120 },
				{ 792, 32, 878, 120 },
				{ 899, 31, 975, 120 },
				{ 993, 33, 1085, 120 }
			}
		};

		mRenderManager.CreateAnimationAsset(runPath, frameAnimationInfo);

		mBackground = new Object({ 0,0, 1920, 1080 }, AnimationInstance(*mRenderManager.GetAnimationAssetOrNull(backgroundPath), 0, 0, 0.2f));

		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				mPlayers[i][j] = new Object({ 100.f * i, 100.f * j , 100.f * (i + 1), 100.f * (j + 1) }, AnimationInstance(*mRenderManager.GetAnimationAssetOrNull(runPath), 0, i, 0.1f * (j + 1)));
			}
		}
	}

	void D2DFirst::Update()
	{
		mTimeManager.Update();
		const float DELTA_TIME = mTimeManager.GetDeltaTime();

		mBackground->Update(DELTA_TIME);
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				mPlayers[i][j]->Update(DELTA_TIME);
			}
		}
	}

	void D2DFirst::Render()
	{
		mRenderManager.BeginDraw();
		mBackground->Render(&mRenderManager);
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				mPlayers[i][j]->Render(&mRenderManager);
			}
		}
		mRenderManager.EndDraw();
	}

	void D2DFirst::Destroy()
	{
		mRenderManager.Release();
		CoUninitialize();
	}
}