#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <d2d1helper.h>

#include "GameProcessor.h"
#include "TimeManger.h"
#include "RenderManger.h"
#include "InputManager.h"
#include "System.h"
#include "TimeManger.h"
#include "RenderManger.h"

namespace entityComponentSystem
{
	class EntityManager;

	class D2DEntityComponentSystem : public gameProcessor::GameProcessor
	{
	public:
		D2DEntityComponentSystem(UINT width, UINT height, std::wstring name);
		virtual ~D2DEntityComponentSystem() = default;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		gameProcessor::TimeManager mTimeManager;
		gameProcessor::RenderManager mRenderManager;
		System mSystem;

		EntityManager* mEntityManager;
	};
}