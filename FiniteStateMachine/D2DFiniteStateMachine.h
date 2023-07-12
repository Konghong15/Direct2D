#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <d2d1helper.h>
#include <vector>

#include "GameProcessor.h"
#include "TimeManger.h"
#include "RenderManger.h"
#include "InputManager.h"
#include "TimeManger.h"
#include "RenderManger.h"
#include "Matrix3X3.h"

namespace finiteStateMachine
{
	class EntityManager;
	class Player;
	class Enemy;
	class Weapon;

	class D2DFiniteStateMachine : public gameProcessor::GameProcessor
	{
	public:
		D2DFiniteStateMachine(UINT width, UINT height, std::wstring name);
		virtual ~D2DFiniteStateMachine() = default;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		enum { SWPAN_MONSTER_COUNT = 20 };

		gameProcessor::TimeManager mTimeManager;
		gameProcessor::RenderManager mRenderManager;
		gameProcessor::InputManager mInputManager;

		Player* mPlayer;
		Enemy* mEnemies[SWPAN_MONSTER_COUNT];
		std::vector<Weapon*> mWeapons;
		gameProcessor::Matrix3X3 mScreenTransform;
	};
}