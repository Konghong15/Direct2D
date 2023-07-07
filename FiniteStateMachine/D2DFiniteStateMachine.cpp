#include "D2DFiniteStateMachine.h"
#include "Player.h"
#include "hRectangle.h"
#include "AnimationAsset.h"
#include "AnimationInstance.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Toungu.h"

namespace finiteStateMachine
{
	D2DFiniteStateMachine::D2DFiniteStateMachine(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mPlayer(nullptr)
	{
	}

	void D2DFiniteStateMachine::Init()
	{
		using namespace gameProcessor;

		HRESULT hr;
		hr = CoInitialize(NULL);
		assert(SUCCEEDED(hr));

		mRenderManager.Init();
		mTimeManager.Init();
		mInputManager.Init();

		mScreenTransform = gameProcessor::Matrix3X3::GetScale(1, -1) * gameProcessor::Matrix3X3::GetTranslate(GetWidth() / 2, GetHeight() / 2);

		const WCHAR* playerPath = L"../resource/character.png";
		const WCHAR* weaponPath = L"../resource/weapon.png";
		const WCHAR* enemyPath = L"../resource/enemy.png";
		const WCHAR* playerKey = L"player";
		const WCHAR* playerWeaponKey = L"playerWeaponKey";
		const WCHAR* enemyKey = L"enemyKey";
		const WCHAR* enemyWeaponKey = L"enemyWeaponKey";

		std::vector<std::vector<hRectangle>> frameAnimationInfo;
	
		frameAnimationInfo =
		{
			{
				{9, 10, 23,	26 },
				{41, 10, 55, 26 },
				{73, 11	, 87, 26 },
				{105, 11, 119, 26 }
			},
			{
				{ 167, 11, 182, 26 },
				{ 199, 10, 214, 26 },
				{ 231, 9, 246, 26 },
				{ 263, 10, 278, 26 }
			}
		};
		mRenderManager.CreateAnimationAsset(playerKey, playerPath, frameAnimationInfo);

		frameAnimationInfo =
		{
			{
				{ 1, 146, 20, 156},
				{ 1, 157, 48, 199 },
				{ 49, 157, 96, 199 },
				{ 97, 157, 144, 199 },
				{ 1, 200, 48, 242 },
				{ 49, 200, 96, 242 },
				{ 97,200, 144, 242 }
			}
		};
		mRenderManager.CreateAnimationAsset(playerWeaponKey, weaponPath, frameAnimationInfo);

		frameAnimationInfo =
		{
			{
				{ 1, 1, 108, 90 },
				{ 109, 1, 216, 90 },
				{ 217, 1, 324, 90 },
			},
			{
				{ 1, 106, 108, 195 },
				{ 109, 106, 216, 195 },
				{ 217, 106, 324, 195 },
				{ 325, 106, 432, 195 },
				{ 1, 196, 108, 285 },
				{ 109, 196, 216, 285 },
				{ 217, 196, 324, 285 },
				{ 325, 196, 432, 285 },
				{ 1, 286, 108, 375 },
				{ 109, 286, 216, 375 }
			},
			{
				{ 1, 466, 108, 555 },
				{ 109, 466, 216, 555 },
				{ 217, 466, 324, 555 },
				{ 325, 466, 432, 555 },
				{ 1, 556, 108, 645 },
				{ 109, 556, 216, 645 },
				{ 217, 556, 324, 645 },
				{ 325, 556, 432, 645 }
			},
			{
				{ 1	,646, 108, 735 },
				{ 109, 646, 216, 735 },
				{ 1, 736, 108, 825 },
				{ 109, 736, 216, 825 },
				{ 217, 736, 324, 825 },
				{ 325, 736, 432, 825 },

			},
			{
				{ 1, 852, 108, 941 },
				{ 109, 852, 216, 941 },
				{ 217, 852, 324, 941 },
				{ 325, 852, 432, 941 },
				{ 1, 942, 108, 1031 },
				{ 109, 942, 216, 1031 },
				{ 217, 942, 324, 1031 },
				{ 1, 1032, 108, 1121 },
				{ 109, 1032, 216, 1121 },
				{ 217, 1032, 324, 1121 },
				{ 325, 1032, 432, 1121 },
				{ 1, 1122, 108, 1211 },
				{ 109, 1122, 216, 1211 },
				{ 217, 1122, 324, 1211 }
			}
		};
		mRenderManager.CreateAnimationAsset(enemyKey, enemyPath, frameAnimationInfo);

		frameAnimationInfo =
		{
			{
				{166, 826, 247,	840},
				{248, 826, 329,	840},
				{330, 826, 411,	840}
			}
		};

		mRenderManager.CreateAnimationAsset(enemyWeaponKey, enemyPath, frameAnimationInfo);

		Weapon* weapon = new Weapon(new AnimationInstance(*mRenderManager.GetAnimationAssetOrNull(playerWeaponKey), 0, 0, 0.1f), { 25, 25, 0, 0 }, 400.f, 200.f);
		mPlayer = new Player(new AnimationInstance(*mRenderManager.GetAnimationAssetOrNull(playerKey), 0, 0, 0.2f), { -30, 30, 30, -30 }, weapon, 300);

		weapon->SetParent(mPlayer);
		mPlayer->AddChild(weapon);

		for (int i = 0; i < 10; ++i)
		{
			int randX = rand() % GetWidth() - GetWidth() / 2;
			int randY = rand() % GetHeight() - GetHeight() / 2;
			weapon = new Toungu(new AnimationInstance(*mRenderManager.GetAnimationAssetOrNull(enemyWeaponKey), 0, 0, 0.1f), { 0, 25, 50, -25 }, 400.f, 200.f);
			mEnemy[i] = new Enemy(new AnimationInstance(*mRenderManager.GetAnimationAssetOrNull(enemyKey), 0, 0, 0.2f), { -100.f + randX, 100.f + randY, 100.f + randX, -100.f + randY }, weapon, 50, 700, 200);

			mEnemy[i]->SetPlayer(mPlayer);
			weapon->SetParent(mEnemy[i]);
			mEnemy[i]->AddChild(weapon);
		}
	}

	void D2DFiniteStateMachine::Update()
	{
		mTimeManager.Update();
		mInputManager.Update();

		const float DELTA_TIME = mTimeManager.GetDeltaTime();

		Enemy* minEnemy = mEnemy[0];
		gameProcessor::Vector2 minVector = mEnemy[0]->GetWorldRectangle().GetCenter() - mPlayer->GetWorldRectangle().GetCenter();
		float minDistance = minVector.GetMagnitude();
		for (int i = 1; i < 10; ++i)
		{
			gameProcessor::Vector2 vector = mEnemy[i]->GetWorldRectangle().GetCenter() - mPlayer->GetWorldRectangle().GetCenter();
			float distance = vector.GetMagnitude();
			if (minDistance > distance)
			{
				minVector = vector;
				minDistance = distance;
			}
		}

		minVector.Normalize();

		mPlayer->HandleInput(&mInputManager);
		mPlayer->Update(DELTA_TIME);
		mPlayer->SetAttackDirection(minVector);

		for (int i = 0; i < 10; ++i)
		{
			mEnemy[i]->Update(DELTA_TIME);
		}
	}

	void D2DFiniteStateMachine::Render()
	{
		mRenderManager.BeginDraw();

		mPlayer->Render(&mRenderManager, mScreenTransform);
		for (int i = 0; i < 10; ++i)
		{
			mEnemy[i]->Render(&mRenderManager, mScreenTransform);
		}

		mRenderManager.EndDraw();
	}

	void D2DFiniteStateMachine::Destroy()
	{
		delete mPlayer;

		for (int i = 0; i < 10; ++i)
		{
			delete mEnemy[i];
		}

		mRenderManager.Release();
	}
}