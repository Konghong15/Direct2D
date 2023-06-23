#include "D2DComponentBased.h"

namespace componentBased
{
	using namespace gameProcessor;

	D2DComponentBased::D2DComponentBased(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mTimeManager()
		, mRenderManager()
	{
	}

	void D2DComponentBased::Init()
	{
		HRESULT hr;
		hr = CoInitialize(NULL);
		assert(SUCCEEDED(hr));

		mRenderManager.Init();
		mTimeManager.Init();
	}

	void D2DComponentBased::Update()
	{
		mTimeManager.Update();
		const float DELTA_TIME = mTimeManager.GetDeltaTime();
	}

	void D2DComponentBased::Render()
	{
		mRenderManager.BeginDraw();



		mRenderManager.EndDraw();
	}

	void D2DComponentBased::Destroy()
	{
		mRenderManager.Release();
		CoUninitialize();
	}
}