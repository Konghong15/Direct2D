#include "Collision.h"
#include "D2DCamara.h"

namespace camara
{
	D2DCamara::D2DCamara(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mCamara(width, height, 200)
	{
	}

	void D2DCamara::Init()
	{
		mTimeManager.Init();
		mRenderManager.Init();
		mInputManager.Init();

		mObjects.reserve(128);

		const  int HALF_WIDTH = mWidth / 2;
		const  int HALF_HEIGHT = mHeight / 2;
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				mObjects.push_back(gameProcessor::hRectangle(i * 500 - HALF_WIDTH, j * 500 - HALF_HEIGHT, (i + 1) * 500 - HALF_WIDTH, (j + 1) * 500 - HALF_HEIGHT));
			}
		}
	}

	void D2DCamara::Update()
	{
		mTimeManager.Update();
		mInputManager.Update();
		const float DELTA_TIME = mTimeManager.GetDeltaTime();

		mCamara.Update(&mInputManager, DELTA_TIME * 10);
	}

	void D2DCamara::Render()
	{
		mRenderManager.BeginDraw();

		gameProcessor::Matrix3X3 inverse;
		gameProcessor::Matrix3X3::TryInverse(mCamara.GetTransform(), &inverse);

		gameProcessor::hRectangle clippingRect = mCamara.GetClippingRectangle();

		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			if (gameProcessor::Collision::CheckRectangleToRectangle(clippingRect, (*iter)))
			{
				mRenderManager.DrawRectangle((*iter), inverse);
			}
		}

		mRenderManager.EndDraw();
	}

	void D2DCamara::Destroy()
	{
		mRenderManager.Release();
	}
}