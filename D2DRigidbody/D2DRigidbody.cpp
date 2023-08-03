#include "D2DRigidbody.h"

#include "GameObject.h"
#include "Transform.h"
#include "CircleCollider.h"

#include "Circle.h"
#include "CircleCollider.h"
#include "Rigidbody.h"
#include "BounceBallComponent.h"

namespace d2dRigidbody
{
	D2DRigidbody::D2DRigidbody(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mLeftWall(nullptr)
		, mRightWall(nullptr)
		, mGround(nullptr)
		, mCeiling(nullptr)
		, mBounceBall(nullptr)
		, mDummy{ nullptr, }
	{
	}

	void D2DRigidbody::Init()
	{
		GameProcessor::Init();
		using namespace d2dFramework;

		Transform* transform;
		CircleCollider* circleCollider;
		Rigidbody* rigidbody;

		// make player, dummy
		{
			float radius = 50.f;

			mBounceBall = new GameObject();
			transform->SetTranslate({ GetWidth() * 0.5f, GetHeight() * 0.5f });
			circleCollider->SetRadius(radius);

			rigidbody->SetMass(100);

			for (size_t i = 0u; i < DUMMY_COUNT; ++i)
			{

				radius = (rand() % 200) + 10;

				transform->SetTranslate({ GetWidth() / static_cast<float>(DUMMY_COUNT) * i, static_cast<float>(rand() % GetHeight()) });
				circleCollider->SetRadius(radius);

				rigidbody->SetMass(0);
			}
		}
	}

	void D2DRigidbody::Update()
	{
		GameProcessor::Update();
	}

	void D2DRigidbody::Destroy()
	{

		GameProcessor::Destroy();
	}
}