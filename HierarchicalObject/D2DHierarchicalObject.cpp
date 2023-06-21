#include "D2DHierarchicalObject.h"

namespace hierarchicalObject
{
	using namespace gameProcessor;

	D2DHierarchicalObject::D2DHierarchicalObject(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mTimeManager()
		, mRenderManager()
		, mGameObject1(nullptr)
		, mGameObject2(nullptr)
		, mGameObject3(nullptr)
	{
	}

	void D2DHierarchicalObject::Init()
	{
		HRESULT hr;
		hr = CoInitialize(NULL);
		assert(SUCCEEDED(hr));

		mRenderManager.Init();
		mTimeManager.Init();

		const float OBJECT_SIZE[4] = { 50.f, 25.f, 10.f , 5.f };
		const UINT WINDOWS_CENTER_X = mWidth / 2;
		const UINT WINDOWS_CENTER_Y = mHeight / 2;

		hRectangle rectangle =
		{
			WINDOWS_CENTER_X - OBJECT_SIZE[0],
			WINDOWS_CENTER_Y - OBJECT_SIZE[0],
			WINDOWS_CENTER_X + OBJECT_SIZE[0],
			WINDOWS_CENTER_Y + OBJECT_SIZE[0]
		};
		mGameObject1 = new GameObject(rectangle, 0.f, 1.f);

		rectangle =
		{
			WINDOWS_CENTER_X / 3 - OBJECT_SIZE[1],
			WINDOWS_CENTER_Y / 3 - OBJECT_SIZE[1],
			WINDOWS_CENTER_X / 3 + OBJECT_SIZE[1],
			WINDOWS_CENTER_Y / 3 + OBJECT_SIZE[1]
		};
		mGameObject2 = new GameObject(rectangle, 0.f, 2.f, mGameObject1);

		rectangle =
		{
			WINDOWS_CENTER_X / 10 - OBJECT_SIZE[2],
			WINDOWS_CENTER_Y / 10 - OBJECT_SIZE[2],
			WINDOWS_CENTER_X / 10 + OBJECT_SIZE[2],
			WINDOWS_CENTER_Y / 10 + OBJECT_SIZE[2]
		};
		mGameObject3 = new GameObject(rectangle, 0.f, 3.f, mGameObject2);

		rectangle =
		{
			WINDOWS_CENTER_X / 20 - OBJECT_SIZE[3],
			WINDOWS_CENTER_Y / 20 - OBJECT_SIZE[3],
			WINDOWS_CENTER_X / 20 + OBJECT_SIZE[3],
			WINDOWS_CENTER_Y / 20 + OBJECT_SIZE[3]
		};
		mGameObject4 = new GameObject(rectangle, 0.f, 4.f, mGameObject3);
	}

	void D2DHierarchicalObject::Update()
	{
		mTimeManager.Update();
		const float DELTA_TIME = mTimeManager.GetDeltaTime();
		mGameObject1->Update(DELTA_TIME);
	}

	void D2DHierarchicalObject::Render()
	{
		mRenderManager.BeginDraw();

		mGameObject1->Render(&mRenderManager);

		mRenderManager.EndDraw();
	}

	void D2DHierarchicalObject::Destroy()
	{
		delete mGameObject1;
		delete mGameObject2;
		delete mGameObject3;
		mRenderManager.Release();
		CoUninitialize();
	}
}