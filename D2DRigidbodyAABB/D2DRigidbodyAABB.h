#pragma once

#include "GameProcessor.h"

namespace d2dFramework
{
	class GameObject;
}

namespace d2dRigidbodyAABB
{
	class D2DRigidbodyAABB : public d2dFramework::GameProcessor
	{
	public:
		D2DRigidbodyAABB(UINT width, UINT height, std::wstring name);
		virtual ~D2DRigidbodyAABB() = default;

		virtual void Init() override;
		virtual void Destroy() override;

	private:
		enum { DUMMY_COUNT = 10u };

		d2dFramework::GameObject* mLeftWall;
		d2dFramework::GameObject* mRightWall;
		d2dFramework::GameObject* mGround;
		d2dFramework::GameObject* mPlatform1;
		d2dFramework::GameObject* mPlatform2;

		d2dFramework::GameObject* mBoxPlayer;
		d2dFramework::GameObject* mCirclePlayer;

		d2dFramework::GameObject* mDummy[DUMMY_COUNT];
	};
}