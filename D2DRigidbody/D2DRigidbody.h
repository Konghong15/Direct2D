#pragma once

#include "GameProcessor.h"

namespace d2dFramework
{
	class GameObject;
}

namespace d2dRigidbody
{
	class D2DRigidbody : public d2dFramework::GameProcessor
	{
	public:
		D2DRigidbody(UINT width, UINT height, std::wstring name);
		virtual ~D2DRigidbody() = default;

		virtual void Init() override;
		virtual void Update() override;
		virtual void Destroy() override;

	private:
		enum { DUMMY_COUNT = 10u };

		d2dFramework::GameObject* mLeftWall;
		d2dFramework::GameObject* mRightWall;
		d2dFramework::GameObject* mGround;
		d2dFramework::GameObject* mCeiling;

		d2dFramework::GameObject* mBounceBall;

		d2dFramework::GameObject* mDummy[DUMMY_COUNT];
	};
}