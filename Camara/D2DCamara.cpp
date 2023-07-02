#include "Helper.h"
#include "Collision.h"
#include "D2DCamara.h"
#include "GameObject.h"
#include "Camara.h"

namespace camara
{
	D2DCamara::D2DCamara(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
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
		for (int i = -25; i < 25; ++i)
		{
			for (int j = -25; j < 25; ++j)
			{
				mObjects.push_back(new GameObject(gameProcessor::hRectangle(i * 500 - HALF_WIDTH, j * 500 - HALF_HEIGHT, (i + 1) * 500 - HALF_WIDTH, (j + 1) * 500 - HALF_HEIGHT), 100.f));
			}
		}

		mPlayer = new Player({ -250, -250, 250, 250 }, 1000);
		mCamara = new Camara(mWidth, mHeight, 200);
		mMiniMapCamara = new Camara(mWidth * 2, mHeight * 2, 200);

		mCamara->SetOwnerObject(mPlayer);
		//mMiniMapCamara->SetOwnerObject(mPlayer);
	}

	void D2DCamara::Destroy()
	{
		delete mPlayer;
		delete mCamara;
		delete mMiniMapCamara;
		mRenderManager.Release();
	}

	void D2DCamara::Update()
	{
		mTimeManager.Update();
		mInputManager.Update();

		const float DELTA_TIME = mTimeManager.GetDeltaTime();

		mPlayer->HandleInput(&mInputManager);

		mPlayer->Update(DELTA_TIME);
		mCamara->Update(&mInputManager, DELTA_TIME);
		mMiniMapCamara->Update(&mInputManager, DELTA_TIME);

		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			(*iter)->Update(DELTA_TIME);
		}
	}

	void D2DCamara::Render()
	{
		mRenderManager.BeginDraw();

		// clipingCamara 
		gameProcessor::Matrix3X3 inverse;
		gameProcessor::Matrix3X3::TryInverse(mCamara->GetTransform(), &inverse);
		gameProcessor::hRectangle clippingRect = mCamara->GetClippingRectangle();
		gameProcessor::Matrix3X3 viewportTransform = gameProcessor::Matrix3X3::GetScale(0.5f, 0.5f) * gameProcessor::Matrix3X3::GetTranslate(mWidth / 2, 0);

		mRenderManager.FillRectangle(gameProcessor::hRectangle(mWidth / 2, 0, mWidth, mHeight)
			, gameProcessor::Matrix3X3::Identity()
			, gameProcessor::Helper::GetRGBA(253, 250, 205, 255));

		mRenderManager.DrawRectangle(gameProcessor::hRectangle(mWidth / 2, 0, mWidth, mHeight)
			, gameProcessor::Matrix3X3::Identity()
			, gameProcessor::Helper::GetRGBA(253, 227, 114, 255));


		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			if (gameProcessor::Collision::CheckRectangleToRectangle(clippingRect, (*iter)->GetWorldRectangle()))
			{
				(*iter)->Render(&mRenderManager, inverse * viewportTransform, gameProcessor::Helper::GetRGBA(0, 0, 0, 255));
			}
		}
		mPlayer->Render(&mRenderManager, inverse * viewportTransform, gameProcessor::Helper::GetRGBA(0, 255, 0, 255));

		// minimap
		gameProcessor::Matrix3X3 minimapInverse;
		gameProcessor::Matrix3X3::TryInverse(mMiniMapCamara->GetTransform(), &minimapInverse);
		gameProcessor::hRectangle minimapClippingRect = mMiniMapCamara->GetClippingRectangle();
		gameProcessor::Matrix3X3 minimapViewportTrasform = gameProcessor::Matrix3X3::GetScale(0.25f, 0.25f) * gameProcessor::Matrix3X3::GetTranslate(mWidth / 2, mHeight / 2);

		mRenderManager.FillRectangle(gameProcessor::hRectangle(mWidth / 2, mHeight / 2, mWidth, mHeight)
			, gameProcessor::Matrix3X3::Identity()
			, gameProcessor::Helper::GetRGBA(253, 250, 205, 255));

		mRenderManager.DrawRectangle(gameProcessor::hRectangle(mWidth / 2, mHeight / 2, mWidth, mHeight)
			, gameProcessor::Matrix3X3::Identity()
			, gameProcessor::Helper::GetRGBA(253, 227, 114, 255));


		unsigned int enemyCount = 0;
		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			if (!gameProcessor::Collision::ContainRectangleToRectangle(minimapClippingRect, (*iter)->GetWorldRectangle()))
			{
				continue;
			}

			if (gameProcessor::Collision::CheckRectangleToRectangle(clippingRect, (*iter)->GetWorldRectangle()))
			{
				++enemyCount;
				(*iter)->Render(&mRenderManager, minimapInverse * minimapViewportTrasform, gameProcessor::Helper::GetRGBA(0, 0, 0, 255));
			}
			else
			{
				(*iter)->Render(&mRenderManager, minimapInverse * minimapViewportTrasform, gameProcessor::Helper::GetRGBA(255, 0, 0, 127));
			}
		}

		mPlayer->Render(&mRenderManager, minimapInverse * minimapViewportTrasform, gameProcessor::Helper::GetRGBA(0, 255, 0, 255));
		mRenderManager.DrawRectangle(mCamara->GetRectangle(), mCamara->GetTransform() * minimapInverse * minimapViewportTrasform);

		// UI
		gameProcessor::Matrix3X3 uiViewportTrasform = gameProcessor::Matrix3X3::ComineMatrix(1, gameProcessor::Matrix3X3::GetScale(0.5f, 1.f));

		mRenderManager.FillRectangle(gameProcessor::hRectangle(0, 0, mWidth, mHeight)
			, gameProcessor::Matrix3X3::ComineMatrix(1, gameProcessor::Matrix3X3::GetScale(0.5f, 1.f))
			, gameProcessor::Helper::GetRGBA(253, 250, 205, 255));

		mRenderManager.DrawRectangle(gameProcessor::hRectangle(0, 0, mWidth, mHeight)
			, gameProcessor::Matrix3X3::ComineMatrix(1, gameProcessor::Matrix3X3::GetScale(0.5f, 1.f))
			, gameProcessor::Helper::GetRGBA(253, 227, 114, 255));

		WCHAR str[256];
		wsprintf(str, L"up, down arrow key : move\nleft, right arrow key : rotate\n\'x\' key zoom out\n\'c\' key zoom in", enemyCount, mObjects.size() - enemyCount);
		mRenderManager.WriteText({ 100, 100, 1900, 800 }, str, 50, gameProcessor::Matrix3X3::Identity());

		wsprintf(str, L"inside enemy count : %d\noutside enemy count : %d", enemyCount, mObjects.size() - enemyCount);
		mRenderManager.WriteText({ 100, 600, 1900, 800 }, str, 50, gameProcessor::Matrix3X3::Identity());

		wsprintf(str, L"FPS : %d", mTimeManager.GetFPS());
		mRenderManager.WriteText({ 100, 800, 1900, 800 }, str, 50, gameProcessor::Matrix3X3::Identity());

		mRenderManager.EndDraw();
	}

}