#include "Collision.h"
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
		mWeapons.reserve(32);

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
			},
			{
				{9, 108, 23, 122 },
				{41, 104, 56, 122 },
				{73, 94, 88, 112 },
				{105, 85, 120, 103 },
				{137, 81, 152, 99 },
				{169, 78, 184, 96 },
				{201, 76, 216, 94 },
				{233, 75, 248, 93 },
				{265, 74, 280, 92 },
				{297, 75, 312, 90 },
				{329, 76, 344, 91 },
				{361, 78, 376, 93 },
				{393, 81, 408, 96 },
				{425, 88, 440, 103 },
				{457, 97, 472, 112 },
				{489, 107, 504,	122	},
				{521, 108, 536,	122	},
				{553, 108, 568,	122	},
				{585, 108, 600,	122	}
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

		Weapon* weapon = new Weapon(new AnimationInstance(*mRenderManager.GetAnimationAssetOrNull(playerWeaponKey), 0, 0, 0.1f), { -25, 0, 0, -25 }, 25, 400.f, 200.f, eOwnerType::Player);
		mPlayer = new Player(new AnimationInstance(*mRenderManager.GetAnimationAssetOrNull(playerKey), 0, 0, 0.2f), { -30, 30, 30, -30 }, 20, weapon, 200);

		weapon->SetParent(mPlayer);
		mPlayer->AddChild(weapon);
		mWeapons.push_back(weapon);

		for (int i = 0; i < SWPAN_MONSTER_COUNT; ++i)
		{
			int randX = rand() % GetWidth() - GetWidth() / 2;
			int randY = rand() % GetHeight() - GetHeight() / 2;
			weapon = new Toungu(new AnimationInstance(*mRenderManager.GetAnimationAssetOrNull(enemyWeaponKey), 0, 0, 0.1f), { -10, 0, 10, -40 }, 25, 400.f, 200.f);
			mEnemies[i] = new Enemy(new AnimationInstance(*mRenderManager.GetAnimationAssetOrNull(enemyKey), 0, 0, 0.1f), { -100.f + randX, 100.f + randY, 100.f + randX, -100.f + randY }, 50, weapon, 200, 700, 200);

			mEnemies[i]->SetPlayer(mPlayer);
			weapon->SetParent(mEnemies[i]);
			mEnemies[i]->AddChild(weapon);

			mWeapons.push_back(weapon);
		}
	}

	void D2DFiniteStateMachine::Update()
	{
		// manager update
		mTimeManager.Update();
		mInputManager.Update();

		const float DELTA_TIME = mTimeManager.GetDeltaTime();

		// player detect emeny
		Enemy* minEnemy = mEnemies[0];
		gameProcessor::Vector2 minVector = mEnemies[0]->GetWorldRectangle().GetCenter() - mPlayer->GetWorldRectangle().GetCenter();
		float minDistance = minVector.GetMagnitude();
		for (int i = 1; i < SWPAN_MONSTER_COUNT; ++i)
		{
			gameProcessor::Vector2 vector = mEnemies[i]->GetWorldRectangle().GetCenter() - mPlayer->GetWorldRectangle().GetCenter();
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

		// check collision
		for (Weapon* weapon : mWeapons)
		{
			if (weapon->GetState() == eWeaponState::Idle)
			{
				continue;
			}

			if (weapon->GetOwnerType() == eOwnerType::Enemy)
			{
				if (gameProcessor::Collision::CheckCircleToCircle(mPlayer->GetWorldCollider(), weapon->GetWorldCollider()))
				{
					mPlayer->OnCollision();
				}
			}
			else
			{
				for (int i = 0; i < SWPAN_MONSTER_COUNT; ++i)
				{
					if (gameProcessor::Collision::CheckCircleToCircle(mEnemies[i]->GetWorldCollider(), weapon->GetWorldCollider()))
					{
						mEnemies[i]->SetIsAlive(false);
						break;
					}
				}
			}
		}

		for (int i = 0; i < SWPAN_MONSTER_COUNT; ++i)
		{
			for (int j = i + 1; j < SWPAN_MONSTER_COUNT; ++j)
			{
				gameProcessor::Circle lhs = mEnemies[i]->GetWorldCollider();
				gameProcessor::Circle rhs = mEnemies[j]->GetWorldCollider();

				if (gameProcessor::Collision::CheckCircleToCircle(lhs, rhs))
				{
					gameProcessor::Vector2 vec = lhs.GetCenter() - rhs.GetCenter();
					gameProcessor::Vector2 oppositeVec = vec * -1;
					float collisionDistance = lhs.GetRadius() + rhs.GetRadius() - vec.GetMagnitude();

					vec.Normalize();
					oppositeVec.Normalize();
					vec = vec * collisionDistance * 0.5f;
					oppositeVec = oppositeVec * collisionDistance * 0.5f;

					mEnemies[i]->SetTranslate(mEnemies[i]->GetTraslate() + vec);
					mEnemies[j]->SetTranslate(mEnemies[j]->GetTraslate() + oppositeVec);
				}
			}
		}

		// enemy update 
		for (int i = 0; i < SWPAN_MONSTER_COUNT; ++i)
		{
			mEnemies[i]->Update(DELTA_TIME);
		}
	}

	void D2DFiniteStateMachine::Render()
	{
		mRenderManager.BeginDraw();

		for (int i = 0; i < SWPAN_MONSTER_COUNT; ++i)
		{
			mEnemies[i]->Render(&mRenderManager, mScreenTransform);
		}
		mPlayer->Render(&mRenderManager, mScreenTransform);

		mRenderManager.EndDraw();
	}

	void D2DFiniteStateMachine::Destroy()
	{
		delete mPlayer;

		for (int i = 0; i < SWPAN_MONSTER_COUNT; ++i)
		{
			delete mEnemies[i];
		}

		mRenderManager.Release();
	}
}