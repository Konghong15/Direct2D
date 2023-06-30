#include "Helper.h"
#include "Collision.h"
#include "D2DCamara.h"
#include "GameObject.h"

namespace camara
{
	D2DCamara::D2DCamara(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mPlayerCamara(width / 2, height, 200)
		, mCamara(width, height, 200)
		, mMiniMapCamara(width * 2, height * 2, 200)
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
				mObjects.push_back(new GameObject(gameProcessor::hRectangle(i * 500 - HALF_WIDTH, j * 500 - HALF_HEIGHT, (i + 1) * 500 - HALF_WIDTH, (j + 1) * 500 - HALF_HEIGHT), 100.f));
			}
		}

		mPlayer = new Player({ -250, -250, 250,250 }, 200);
		mPlayerCamara.SetOwnerObject(mPlayer);
	}

	void D2DCamara::Update()
	{
		mTimeManager.Update();
		mInputManager.Update();

		const float DELTA_TIME = mTimeManager.GetDeltaTime();

		mPlayer->HandleInput(&mInputManager);
		mPlayer->Update(DELTA_TIME);

		mPlayerCamara.Update(&mInputManager, DELTA_TIME * 10);
		mCamara.Update(&mInputManager, DELTA_TIME * 10);
		mMiniMapCamara.Update(&mInputManager, DELTA_TIME * 10);


		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			(*iter)->Update(DELTA_TIME);
		}
	}

	void D2DCamara::Render()
	{
		mRenderManager.BeginDraw();

		// playerCamara
		mRenderManager.FillRectangle(gameProcessor::hRectangle(0, 0, mWidth, mHeight)
			, gameProcessor::Matrix3X3::ComineMatrix(1, gameProcessor::Matrix3X3::GetScale(0.5f, 1.f))
			, gameProcessor::Helper::GetRGBA(253, 250, 205, 255));

		mRenderManager.DrawRectangle(gameProcessor::hRectangle(0, 0, mWidth, mHeight)
			, gameProcessor::Matrix3X3::ComineMatrix(1, gameProcessor::Matrix3X3::GetScale(0.5f, 1.f))
			, gameProcessor::Helper::GetRGBA(253, 227, 114, 255));

		gameProcessor::Matrix3X3 playerCamaraInverse;
		gameProcessor::Matrix3X3::TryInverse(mPlayerCamara.GetTransform(), &playerCamaraInverse);
		gameProcessor::hRectangle playerCamaraClippingRect = mPlayerCamara.GetClippingRectangle();

		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			if (gameProcessor::Collision::CheckRectangleToRectangle(playerCamaraClippingRect, (*iter)->GetRectangle()))
			{
				(*iter)->Render(&mRenderManager, playerCamaraInverse, gameProcessor::Helper::GetRGBA(0, 0, 0, 255));
			}
		}
		mPlayer->Render(&mRenderManager, playerCamaraInverse, gameProcessor::Helper::GetRGBA(0, 255, 0, 255));


		// clipingCamara 
		mRenderManager.FillRectangle(gameProcessor::hRectangle(0, 0, mWidth, mHeight)
			, gameProcessor::Matrix3X3::ComineMatrix(2, gameProcessor::Matrix3X3::GetScale(0.5f, 0.5f), gameProcessor::Matrix3X3::GetTranslate(mWidth / 2, 0))
			, gameProcessor::Helper::GetRGBA(253, 250, 205, 255));

		mRenderManager.DrawRectangle(gameProcessor::hRectangle(0, 0, mWidth, mHeight)
			, gameProcessor::Matrix3X3::ComineMatrix(2, gameProcessor::Matrix3X3::GetScale(0.5f, 0.5f), gameProcessor::Matrix3X3::GetTranslate(mWidth / 2, 0))
			, gameProcessor::Helper::GetRGBA(253, 227, 114, 255));

		gameProcessor::Matrix3X3 inverse;
		gameProcessor::Matrix3X3::TryInverse(mCamara.GetTransform(), &inverse);
		gameProcessor::hRectangle clippingRect = mCamara.GetClippingRectangle();
		gameProcessor::Matrix3X3 viewportTransform = gameProcessor::Matrix3X3::GetScale(0.5f, 0.5f) * gameProcessor::Matrix3X3::GetTranslate(mWidth / 2, 0);

		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			if (gameProcessor::Collision::CheckRectangleToRectangle(clippingRect, (*iter)->GetRectangle()))
			{
				(*iter)->Render(&mRenderManager, inverse * viewportTransform, gameProcessor::Helper::GetRGBA(0, 0, 0, 255));
			}
		}
		if (gameProcessor::Collision::CheckRectangleToRectangle(clippingRect, mPlayer->GetRectangle()))
		{
			mPlayer->Render(&mRenderManager, inverse * viewportTransform, gameProcessor::Helper::GetRGBA(0, 255, 0, 255));
		}


		// minimap
		mRenderManager.FillRectangle(gameProcessor::hRectangle(0, 0, mWidth, mHeight)
			, gameProcessor::Matrix3X3::ComineMatrix(2, gameProcessor::Matrix3X3::GetScale(0.5f, 0.5f), gameProcessor::Matrix3X3::GetTranslate(mWidth / 2, mHeight / 2))
			, gameProcessor::Helper::GetRGBA(253, 250, 205, 255));

		mRenderManager.DrawRectangle(gameProcessor::hRectangle(0, 0, mWidth, mHeight)
			, gameProcessor::Matrix3X3::ComineMatrix(2, gameProcessor::Matrix3X3::GetScale(0.5f, 0.5f), gameProcessor::Matrix3X3::GetTranslate(mWidth / 2, mHeight / 2))
			, gameProcessor::Helper::GetRGBA(253, 227, 114, 255));

		gameProcessor::Matrix3X3 minimapInverse;
		gameProcessor::Matrix3X3::TryInverse(mMiniMapCamara.GetTransform(), &minimapInverse);
		gameProcessor::Matrix3X3 minimapTrasform = gameProcessor::Matrix3X3::GetScale(0.25f, 0.25f) * gameProcessor::Matrix3X3::GetTranslate(mWidth / 2, mHeight / 2);
		gameProcessor::hRectangle minimapClippingRect = mMiniMapCamara.GetClippingRectangle();

		unsigned int enemyCount = 0;
		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			if (!gameProcessor::Collision::ContainRectangleToRectangle(minimapClippingRect, (*iter)->GetRectangle()))
			{
				continue;
			}

			if (gameProcessor::Collision::CheckRectangleToRectangle(clippingRect, (*iter)->GetRectangle())) // && gameProcessor::Collision::ContainRectangleToRectangle(minimapClippingRect, (*iter)))
			{
				++enemyCount;
				(*iter)->Render(&mRenderManager, minimapInverse * minimapTrasform, gameProcessor::Helper::GetRGBA(0, 0, 0, 255));
			}
			else
			{
				(*iter)->Render(&mRenderManager, minimapInverse * minimapTrasform, gameProcessor::Helper::GetRGBA(255, 0, 0, 127));
			}
		}
		if (gameProcessor::Collision::CheckRectangleToRectangle(clippingRect, mPlayer->GetRectangle()) && gameProcessor::Collision::ContainRectangleToRectangle(minimapClippingRect, mPlayer->GetRectangle()))
		{
			mPlayer->Render(&mRenderManager, minimapInverse * minimapTrasform, gameProcessor::Helper::GetRGBA(0, 255, 0, 255));
		}

		WCHAR str[256];
		wsprintf(str, L"inside enemy count : %d\noutside enemy count : %d", enemyCount, mObjects.size() - enemyCount);
		mRenderManager.WriteText({ 0,0, 1900, 800 }, str, 20, gameProcessor::Matrix3X3::Identity());

		mRenderManager.EndDraw();
	}

	void D2DCamara::Destroy()
	{
		mRenderManager.Release();
	}
}