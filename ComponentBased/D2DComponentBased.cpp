#include "D2DComponentBased.h"
#include "OldObject.h"

namespace componentBased
{
	using namespace gameProcessor;

	D2DComponentBased::D2DComponentBased(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mTimeManager()
		, mRenderManager()
		, mInputManager()
	{
	}

	void D2DComponentBased::Init()
	{
		HRESULT hr;
		hr = CoInitialize(NULL);
		assert(SUCCEEDED(hr));

		mRenderManager.Init();
		mTimeManager.Init();
		mInputManager.Init();
		//OldObject(gameProcessor::Vector2 scale, float rotateInRadian, gameProcessor::Vector2 translate, gameProcessor::Vector2 direction, float speed, float accelerationIncrement, float maxAcceleration, const gameProcessor::hRectangle& rectangle);

		Vector2 scale(1.f, 1.f);
		float rotationInRadian = 0.f;
		Vector2 traslation(800.f, 600.f);
		Vector2 direction(0.f, 1.f);
		float speed = 10.f;
		float accelationIncrement = 5.f;
		float maxAccelration = 50.f;
		hRectangle rectangle = { -50, -50, 50,50 };

		mOldObject = new OldObject(scale, rotationInRadian, traslation, direction, speed, accelationIncrement, maxAccelration, rectangle);
	}

	void D2DComponentBased::Update()
	{
		mTimeManager.Update();
		mInputManager.Update();
		const float DELTA_TIME = mTimeManager.GetDeltaTime();

		mOldObject->Update(&mInputManager, DELTA_TIME);
	}

	void D2DComponentBased::Render()
	{
		mRenderManager.BeginDraw();

		mOldObject->Render(&mRenderManager);

		mRenderManager.EndDraw();
	}

	void D2DComponentBased::Destroy()
	{
		delete mOldObject;
		mRenderManager.Release();
		CoUninitialize();
	}
}