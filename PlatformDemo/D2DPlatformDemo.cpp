#include "D2DPlatformDemo.h"
#include "PlatformObject.h"
#include "Collision.h"

namespace platform
{
	using namespace gameProcessor;

	D2DPlatformDemo::D2DPlatformDemo(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mCamara(width, height)
	{
	}

	void D2DPlatformDemo::Init()
	{
		GameProcessor::Init();
		mPlayer = new PlatformObject({ -25, -100, 25, -200 }, 10.f, 10.f, 5.f, -9.8f);
		mObstacle0 = new Obstacle({ 100, 800, 150, 0 });
		mObstacle1 = new Obstacle({ -200, 800, -150, -200 });
	}

	void D2DPlatformDemo::Update()
	{
		GameProcessor::Update();
		const float DELTA_TIME = GameProcessor::GetTimeManager()->GetDeltaTime();

		const gameProcessor::hRectangle camaraWorldRectangle = mCamara.GetLocalRectangle() * mCamara.GetTrasform();
		const gameProcessor::hRectangle playerWorldRectangle = mPlayer->GetLocalRectangle() * mPlayer->GetTransformInfo().WorldTransform;

		const gameProcessor::Vector2 traslate = mPlayer->GetTransformInfo().Translate;
		mCamara.SetTraslate(traslate.GetX(), traslate.GetY());
		if (!gameProcessor::Collision::CheckRectangleToRectangle(camaraWorldRectangle, playerWorldRectangle))
		{
			float diffrenceX = playerWorldRectangle.GetCenter().GetX() - camaraWorldRectangle.GetCenter().GetX();
			mCamara.AddTraslate(diffrenceX * 2, 0);
		}

		mPlayer->HandleCollision(*mObstacle0);
		mPlayer->HandleCollision(*mObstacle1);

		mPlayer->HandleInput(GetInputManager());

		mPlayer->Update(DELTA_TIME);
	}

	void D2DPlatformDemo::Render()
	{
		GameProcessor::GetRenderManager()->BeginDraw();

		gameProcessor::Matrix3X3 worldToScreenTransform;
		assert(Matrix3X3::TryInverse(mCamara.GetTrasform(), &worldToScreenTransform));
		worldToScreenTransform *= mCamara.GetScreenTrasform();

		mPlayer->Render(GetRenderManager(), worldToScreenTransform);
		mObstacle0->Render(GetRenderManager(), worldToScreenTransform);
		mObstacle1->Render(GetRenderManager(), worldToScreenTransform);

		GameProcessor::GetRenderManager()->EndDraw();
	}

	void D2DPlatformDemo::Destroy()
	{
		GameProcessor::Destroy();
	}
}