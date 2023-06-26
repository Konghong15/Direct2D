#include "D2DComponentBased.h"
#include "OldObject.h"
#include "OldComponentObject.h"
#include "OldMovementComponent.h"
#include "OldRenderComponent.h"
#include "OldTransformComponent.h"

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

		// 변수들
		Vector2 scale(1.f, 1.f);
		float rotationInRadian = 0.f;
		Vector2 translation(400.f, 300.f);
		Vector2 direction(0.f, 1.f);
		float speed = 10.f;
		float accelationIncrement = 5.f;
		float maxAccelration = 50.f;
		hRectangle rectangle = { -50, -50, 50,50 };

		// 모든 상태를 다 가진 형태
		mOldObject = new OldObject(scale, rotationInRadian, translation, direction, speed, accelationIncrement, maxAccelration, rectangle);

		// 구체적인 컴포넌트로 분리된 상태
		translation = { 800.f, 300.f };
		OldTransformComponent transformComponent(scale, rotationInRadian, translation);
		OldMovementComponent movementComponent(direction, speed, accelationIncrement, maxAccelration);
		OldRenderComponent renderComponent(rectangle);
		mOldComponentObject = new OldComponentObject(transformComponent, movementComponent, renderComponent);
	}

	void D2DComponentBased::Update()
	{
		mTimeManager.Update();
		mInputManager.Update();
		const float DELTA_TIME = mTimeManager.GetDeltaTime();

		mOldObject->Update(&mInputManager, DELTA_TIME);

		mOldComponentObject->Update(&mInputManager, DELTA_TIME);
	}

	void D2DComponentBased::Render()
	{
		mRenderManager.BeginDraw();

		mOldObject->Render(&mRenderManager);
		mOldComponentObject->Render(&mRenderManager);

		mRenderManager.EndDraw();
	}

	void D2DComponentBased::Destroy()
	{
		delete mOldObject;
		delete mOldComponentObject;

		mRenderManager.Release();
		CoUninitialize();
	}
}