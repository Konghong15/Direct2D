#include "D2DRigidbody.h"

#include "GameObject.h"
#include "Transform.h"
#include "BoxSprite.h"
#include "CircleCollider.h"

#include "Circle.h"
#include "CircleCollider.h"
#include "CircleSprite.h"
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
		CircleSprite* circleSprite;
		Rigidbody* rigidbody;

		// make player, dummy
		{
			float radius = 50.f;

			mBounceBall = new GameObject();
			transform = mBounceBall->CreateComponent<Transform>();
			transform->SetTranslate({ GetWidth() * 0.5f, GetHeight() * 0.5f });
			circleCollider = mBounceBall->CreateComponent<CircleCollider>();
			circleCollider->SetRadius(radius);
			circleSprite = mBounceBall->CreateComponent<CircleSprite>();
			circleSprite->SetEllipse({ { 0,0 }, radius,radius });
			circleSprite->SetBaseColor({ 1, 0, 0, 0.5f });
			circleSprite->SetBorderColor({ 1, 0, 0, 1.f });
			rigidbody = mBounceBall->CreateComponent<Rigidbody>();
			BounceBallComponent* bounceBall = mBounceBall->CreateComponent<BounceBallComponent>();
			bounceBall->SetSpped({ 1000, 1000 });

			rigidbody->SetMass(100);

			for (size_t i = 0u; i < DUMMY_COUNT; ++i)
			{

				radius = (rand() % 200) + 10;

				mDummy[i] = new GameObject();
				transform = mDummy[i]->CreateComponent<Transform>();
				transform->SetTranslate({ GetWidth() / static_cast<float>(DUMMY_COUNT) * i, static_cast<float>(rand() % GetHeight()) });
				circleCollider = mDummy[i]->CreateComponent<CircleCollider>();
				circleCollider->SetRadius(radius);
				circleSprite = mDummy[i]->CreateComponent<CircleSprite>();
				circleSprite->SetEllipse({ { 0,0 }, radius, radius });
				circleSprite->SetBaseColor({ 1, 0, 0, 0.5f });
				circleSprite->SetBorderColor({ 1, 0, 0, 1.f });
				rigidbody = mDummy[i]->CreateComponent<Rigidbody>();

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
		delete mLeftWall;
		delete mRightWall;
		delete mGround;
		delete mCeiling;
		delete mBounceBall;

		for (size_t i = 0; i < 10; ++i)
		{
			delete mDummy[i];
		}

		GameProcessor::Destroy();
	}
}