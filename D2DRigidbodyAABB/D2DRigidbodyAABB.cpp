#include "D2DRigidbodyAABB.h"

#include "BoxPlayerComponent.h"
#include "PlatformComponent.h"
#include "CirclePlayerComponent.h"

#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "SceneManager.h"
#include "AABBCollider.h"
#include "Rigidbody.h"
#include "CircleCollider.h"
#include "SpriteRenderer.h"
#include "ObjectManager.h"

#include <functional>

namespace d2dRigidbodyAABB
{
	D2DRigidbodyAABB::D2DRigidbodyAABB(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mLeftWall(nullptr)
		, mRightWall(nullptr)
		, mGround(nullptr)
		, mBoxPlayer(nullptr)
		, mDummy{ nullptr, }
		, mCirclePlayer(nullptr)
	{
	}

	void D2DRigidbodyAABB::Init()
	{
		static unsigned int tempId = 20000;
		using namespace d2dFramework;

		GameProcessor::Init();
		getSceneManager()->RegisterScene("hoho", new Scene("hoho"));
		// register Register Scene;

		Transform* transform;
		AABBCollider* aabbCollider;
		Rigidbody* rigidbody;
		SpriteRenderer* spriteRenderer;
		CircleCollider* circleCollider;

		auto createWall = [](Vector2 pos, Vector2 size) -> GameObject*
		{
			GameObject* wall = ObjectManager::GetInstance()->CreateObject(tempId++);
			Transform* transform = wall->CreateComponent<Transform>(tempId++);
			AABBCollider* collider = wall->CreateComponent<AABBCollider>(tempId++);
			SpriteRenderer* renderer = wall->CreateComponent<SpriteRenderer>(tempId++);

			transform->SetTranslate(pos);
			collider->SetSize(size);
			renderer->SetSize(size);
			renderer->SetBaseColor({ 0,0,0,1 });

			return wall;
		};

		{
			float x = GetWidth() * -0.5f;
			float y = 0;
			float w = 100;
			float h = (float)GetHeight();
			mLeftWall = createWall({ x,y }, { w,h });

			x *= -1;
			mRightWall = createWall({ x,y }, { w,h });

			x = 0;
			y = GetHeight() * -0.5f;
			w = (float)GetWidth();
			h = 300;
			mGround = createWall({ x,y }, { w,h });

			x = 500;
			y = 0;
			w = 300;
			h = 100;
			mPlatform1 = createWall({ x,y }, { w,h });
			PlatformComponent* platformComponent = mPlatform1->CreateComponent<PlatformComponent>(tempId++);
			platformComponent->SetIsMovePaused(false);
			platformComponent->SetMoveSpeed(3.f);
			platformComponent->SetMovePositions({
				{ 500, 100},
				{ 500, -200},
				{ 800, -200},
				{ 500, 100}
				});

			x = -500;
			mPlatform2 = createWall({ x,y }, { w,h });
		}

		// make player, dummy
		{
			float size = 200.f;

			mBoxPlayer = ObjectManager::GetInstance()->CreateObject(tempId++);
			transform = mBoxPlayer->CreateComponent<Transform>(tempId++);
			transform->SetTranslate({ 200, 0 });
			aabbCollider = mBoxPlayer->CreateComponent<AABBCollider>(tempId++);
			aabbCollider->SetSize({ size, size });
			spriteRenderer = mBoxPlayer->CreateComponent<SpriteRenderer>(tempId++);
			spriteRenderer->SetSize({ size, size });
			spriteRenderer->SetBaseColor({ 1, 1, 0, 0.5f });
			spriteRenderer->SetBorderColor({ 1, 0, 0, 1.f });
			rigidbody = mBoxPlayer->CreateComponent<Rigidbody>(tempId++);
			BoxPlayerComponent* boxCo = mBoxPlayer->CreateComponent<BoxPlayerComponent>(tempId++);
			boxCo->SetSpped({ 400, 400 });
			rigidbody->SetMass(100);
			rigidbody->SetCOR(0.f);
			mBoxPlayer->SetObjectType(eObjectType::None);

			mCirclePlayer = ObjectManager::GetInstance()->CreateObject(tempId++);
			transform = mCirclePlayer->CreateComponent<Transform>(tempId++);
			transform->SetTranslate({ -200, 0 });
			circleCollider = mCirclePlayer->CreateComponent<CircleCollider>(tempId++);
			circleCollider->SetRadius(size * 0.5f);
			spriteRenderer = mCirclePlayer->CreateComponent<SpriteRenderer>(tempId++);
			spriteRenderer->SetSpriteType(eSpriteType::Circle);
			spriteRenderer->SetSize({ size, size });
			spriteRenderer->SetBaseColor({ 1, 1, 0, 0.5f });
			spriteRenderer->SetBorderColor({ 1, 1, 0, 1.f });
			rigidbody = mCirclePlayer->CreateComponent<Rigidbody>(tempId++);
			CirclePlayerComponent* circleCo = mCirclePlayer->CreateComponent<CirclePlayerComponent>(tempId++);
			circleCo->SetSpped({ 200, 100 });
			rigidbody->SetMass(100);
			rigidbody->SetCOR(0.5f);
			mCirclePlayer->SetObjectType(eObjectType::None);

			//size = 20;
			//for (size_t i = 0u; i < DUMMY_COUNT; ++i)
			//{
			//	float x = 500 / DUMMY_COUNT * i - 500 * 0.5f;

			//	for (size_t j = 0u; j < DUMMY_COUNT; ++j)
			//	{
			//		float y = 300 / DUMMY_COUNT * j - 300 * 0.5f;;
			//		mDummy[i] = ObjectManager::GetInstance()->CreateObject(tempId++);
			//		mDummy[i]->SetObjectType(eObjectType::Enemy);
			//		transform = mDummy[i]->CreateComponent<Transform>(tempId++);
			//		transform->SetTranslate({ x,y });
			//		aabbCollider = mDummy[i]->CreateComponent<AABBCollider>(tempId++);
			//		aabbCollider->SetSize({ size, size });
			//		spriteRenderer = mDummy[i]->CreateComponent<SpriteRenderer>(tempId++);
			//		spriteRenderer->SetSize({ size, size });
			//		spriteRenderer->SetBaseColor({ 1, 0, 0, 0.5f });
			//		spriteRenderer->SetBorderColor({ 1, 0, 0, 1.f });
			//		rigidbody = mDummy[i]->CreateComponent<Rigidbody>(tempId++);

			//		rigidbody->SetMass(size);

			//		//rigidbody->AddVelocity({ rand() % 100 - 50.f,100 });
			//	}
			//}
		}
	}

	void D2DRigidbodyAABB::Destroy()
	{
		using namespace d2dFramework;

		// ObjectManager::GetInstance()->DeletObject(mLeftWall->GetId());
		// ObjectManager::GetInstance()->DeletObject(mRightWall->GetId());
		// ObjectManager::GetInstance()->DeletObject(mGround->GetId());
		// ObjectManager::GetInstance()->DeletObject(mCeiling->GetId());
		//ObjectManager::GetInstance()->DeletObject(mCirclePlayer->GetId());
		//ObjectManager::GetInstance()->DeletObject(mBoxPlayer->GetId());

		//for (size_t i = 0; i < DUMMY_COUNT; ++i)
		//{
		//	ObjectManager::GetInstance()->DeletObject(mDummy[i]->GetId());
		//}

		GameProcessor::Destroy();
	}
}