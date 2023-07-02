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
#include "Entity.h"
#include "EntityManager.h"
#include "System.h"

namespace entityCamara
{
	class GameObject;
	class Camara;

	class D2DEntityCamara : public gameProcessor::GameProcessor
	{
	public:
		D2DEntityCamara(UINT width, UINT height, std::wstring name);
		virtual ~D2DEntityCamara() = default;

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