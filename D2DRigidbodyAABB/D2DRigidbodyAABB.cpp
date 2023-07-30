#include "D2DRigidbodyAABB.h"

#include "GameObject.h"
#include "Transform.h"
#include "BoxSprite.h"

#include "BoxSprite.h"
#include "AABBCollider.h"
#include "Rigidbody.h"
#include "BoxPlayerComponent.h"

#include "CircleCollider.h"
#include "CircleSprite.h"
#include "CirclePlayerComponent.h"

namespace d2dRigidbodyAABB
{
	D2DRigidbodyAABB::D2DRigidbodyAABB(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mLeftWall(nullptr)
		, mRightWall(nullptr)
		, mGround(nullptr)
		, mCeiling(nullptr)
		, mBoxPlayer(nullptr)
		, mDummy{ nullptr, }
		, mCirclePlayer(nullptr)
	{
	}

	void D2DRigidbodyAABB::Init()
	{
		GameProcessor::Init();
		using namespace d2dFramework;
		// register Register Scene;

		Transform* transform;
		AABBCollider* aabbCollider;
		BoxSprite* boxSprite;
		Rigidbody* rigidbody;

		// make player, dummy
		{
			float size = 50.f;

			mBoxPlayer = new GameObject();
			transform = mBoxPlayer->CreateComponent<Transform>();
			transform->SetTranslate({ GetWidth() * 0.6f, GetHeight() * 0.6f });
			aabbCollider = mBoxPlayer->CreateComponent<AABBCollider>();
			aabbCollider->SetSize({ size, size });
			boxSprite = mBoxPlayer->CreateComponent<BoxSprite>();
			boxSprite->SetRectangle({ -size / 2, -size / 2, size / 2, size / 2 });
			boxSprite->SetBaseColor({ 1, 0, 0, 0.5f });
			boxSprite->SetBorderColor({ 1, 0, 0, 1.f });
			rigidbody = mBoxPlayer->CreateComponent<Rigidbody>();
			BoxPlayerComponent* boxCo = mBoxPlayer->CreateComponent<BoxPlayerComponent>();
			boxCo->SetSpped({ 100, 100 });
			rigidbody->SetMass(100);

			mCirclePlayer = new GameObject();
			transform = mCirclePlayer->CreateComponent<Transform>();
			transform->SetTranslate({ GetWidth() * 0.4f, GetHeight() * 0.4f });
			CircleCollider* circleCollider = mCirclePlayer->CreateComponent<CircleCollider>();
			circleCollider->SetRadius(size);
			CircleSprite* circleSprite = mCirclePlayer->CreateComponent<CircleSprite>();
			circleSprite->SetEllipse({ { 0,0 }, size , size });
			boxSprite->SetBaseColor({ 1, 0, 0, 0.5f });
			boxSprite->SetBorderColor({ 1, 0, 0, 1.f });
			rigidbody = mCirclePlayer->CreateComponent<Rigidbody>();
			CirclePlayerComponent* circleCo = mCirclePlayer->CreateComponent<CirclePlayerComponent>();
			circleCo->SetSpped({ 100, 100 });
			rigidbody->SetMass(100);

			for (size_t i = 0u; i < DUMMY_COUNT; ++i)
			{
				size = (rand() % 200) + 10;

				mDummy[i] = new GameObject();
				transform = mDummy[i]->CreateComponent<Transform>();
				transform->SetTranslate({ GetWidth() / static_cast<float>(DUMMY_COUNT) * i, static_cast<float>(rand() % GetHeight()) });
				aabbCollider = mDummy[i]->CreateComponent<AABBCollider>();
				aabbCollider->SetSize({ size, size });
				boxSprite = mDummy[i]->CreateComponent<BoxSprite>();
				boxSprite->SetRectangle({ -size / 2, -size / 2, size / 2 , size / 2 });
				boxSprite->SetBaseColor({ 1, 0, 0, 0.5f });
				boxSprite->SetBorderColor({ 1, 0, 0, 1.f });
				rigidbody = mDummy[i]->CreateComponent<Rigidbody>();

				rigidbody->SetMass(size);
			}
		}
	}

	void D2DRigidbodyAABB::Update()
	{
		GameProcessor::Update();
	}

	void D2DRigidbodyAABB::Destroy()
	{
		delete mLeftWall;
		delete mRightWall;
		delete mGround;
		delete mCeiling;
		delete mCirclePlayer;
		delete mBoxPlayer;

		for (size_t i = 0; i < DUMMY_COUNT; ++i)
		{
			delete mDummy[i];
		}

		GameProcessor::Destroy();
	}
}