#include "D2DRigidbodyAABB.h"

#include <functional>

#include "GameObject.h"
#include "Transform.h"

#include "Scene.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "AABBCollider.h"
#include "Rigidbody.h"
#include "BoxPlayerComponent.h"

#include "CircleCollider.h"
#include "CirclePlayerComponent.h"

#include "SpriteRenderer.h"

#include "ObjectManager.h"


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
		static unsigned int tempId = 20000;
		using namespace d2dFramework;

		GameProcessor::Init();
		getSceneManager()->RegisterScene("hoho", new Scene("hoho"));
		// register Register Scene;

		unsigned int soundId = tempId++;
		getSoundManager()->CreateSoundAsset(soundId, "../resource/Stage12.ogg");
		getSoundManager()->Play(soundId);
		getSoundManager()->SetFrequencyAll(30.f);
		getSoundManager()->Play(soundId);
		getSoundManager()->Play(soundId);


		Transform* transform;
		AABBCollider* aabbCollider;
		Rigidbody* rigidbody;
		SpriteRenderer* spriteRenderer;
		CircleCollider* circleCollider;

		{
			float x = GetWidth() * -0.5f;
			float y = 0;
			float w = 100;
			float h = (float)GetHeight();
			mLeftWall = ObjectManager::GetInstance()->CreateObject(tempId++);
			transform = mLeftWall->CreateComponent<Transform>(tempId++);
			transform->SetTranslate({ x, y });
			aabbCollider = mLeftWall->CreateComponent<AABBCollider>(tempId++);
			aabbCollider->SetSize({ w, h });
			spriteRenderer = mLeftWall->CreateComponent<SpriteRenderer>(tempId++);
			spriteRenderer->SetSize({ w, h });
			spriteRenderer->SetBaseColor({ 1, 0, 0, 0.5f });
			spriteRenderer->SetBorderColor({ 1, 0, 0, 1.f });

			x *= -1;
			mRightWall = ObjectManager::GetInstance()->CreateObject(tempId++);
			transform = mRightWall->CreateComponent<Transform>(tempId++);
			transform->SetTranslate({ x, y });
			aabbCollider = mRightWall->CreateComponent<AABBCollider>(tempId++);
			aabbCollider->SetSize({ w, h });
			spriteRenderer = mRightWall->CreateComponent<SpriteRenderer>(tempId++);
			spriteRenderer->SetSize({ w, h });
			spriteRenderer->SetBaseColor({ 1, 0, 0, 0.5f });
			spriteRenderer->SetBorderColor({ 1, 0, 0, 1.f });

			/*	x = 0;
				y = GetHeight() * -0.5f;
				w = (float)GetWidth();
				h = 300;
				mGround = ObjectManager::GetInstance()->CreateObject(tempId++);
				transform = mGround->CreateComponent<Transform>(tempId++);
				transform->SetTranslate({ x, y });
				aabbCollider = mGround->CreateComponent<AABBCollider>(tempId++);
				aabbCollider->SetSize({ w, h });
				spriteRenderer = mGround->CreateComponent<SpriteRenderer>(tempId++);
				spriteRenderer->SetSize({ w, h });
				spriteRenderer->SetBaseColor({ 1, 0, 0, 0.5f });
				spriteRenderer->SetBorderColor({ 1, 0, 0, 1.f });*/


			mCeiling = ObjectManager::GetInstance()->CreateObject(tempId++);

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
			mBoxPlayer->SetObjectType(eObjectType::Player);

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
			circleCo->SetSpped({ 100, 100 });
			rigidbody->SetMass(0);
			mCirclePlayer->SetParent(mBoxPlayer);
			mCirclePlayer->SetObjectType(eObjectType::Player);

			mCirclePlayer = ObjectManager::GetInstance()->CreateObject(tempId++);
			transform = mCirclePlayer->CreateComponent<Transform>(tempId++);
			transform->SetTranslate({ 200, 0 });
			circleCollider = mCirclePlayer->CreateComponent<CircleCollider>(tempId++);
			circleCollider->SetRadius(size * 0.5f);
			spriteRenderer = mCirclePlayer->CreateComponent<SpriteRenderer>(tempId++);
			spriteRenderer->SetSpriteType(eSpriteType::Circle);
			spriteRenderer->SetSize({ size, size });
			spriteRenderer->SetBaseColor({ 1, 1, 0, 0.5f });
			spriteRenderer->SetBorderColor({ 1, 1, 0, 1.f });
			rigidbody = mCirclePlayer->CreateComponent<Rigidbody>(tempId++);
			circleCo = mCirclePlayer->CreateComponent<CirclePlayerComponent>(tempId++);
			circleCo->SetSpped({ 100, 100 });
			rigidbody->SetMass(0);
			mCirclePlayer->SetParent(mBoxPlayer);
			mCirclePlayer->SetObjectType(eObjectType::Player);

			mCirclePlayer = ObjectManager::GetInstance()->CreateObject(tempId++);
			transform = mCirclePlayer->CreateComponent<Transform>(tempId++);
			transform->SetTranslate({ 0, 200 });
			circleCollider = mCirclePlayer->CreateComponent<CircleCollider>(tempId++);
			circleCollider->SetRadius(size * 0.5f);
			spriteRenderer = mCirclePlayer->CreateComponent<SpriteRenderer>(tempId++);
			spriteRenderer->SetSpriteType(eSpriteType::Circle);
			spriteRenderer->SetSize({ size, size });
			spriteRenderer->SetBaseColor({ 1, 1, 0, 0.5f });
			spriteRenderer->SetBorderColor({ 1, 1, 0, 1.f });
			rigidbody = mCirclePlayer->CreateComponent<Rigidbody>(tempId++);
			 circleCo = mCirclePlayer->CreateComponent<CirclePlayerComponent>(tempId++);
			circleCo->SetSpped({ 100, 100 });
			rigidbody->SetMass(0);
			mCirclePlayer->SetParent(mBoxPlayer);
			mCirclePlayer->SetObjectType(eObjectType::Player);

			mCirclePlayer = ObjectManager::GetInstance()->CreateObject(tempId++);
			transform = mCirclePlayer->CreateComponent<Transform>(tempId++);
			transform->SetTranslate({ 0, -200 });
			circleCollider = mCirclePlayer->CreateComponent<CircleCollider>(tempId++);
			circleCollider->SetRadius(size * 0.5f);
			spriteRenderer = mCirclePlayer->CreateComponent<SpriteRenderer>(tempId++);
			spriteRenderer->SetSpriteType(eSpriteType::Circle);
			spriteRenderer->SetSize({ size, size });
			spriteRenderer->SetBaseColor({ 1, 1, 0, 0.5f });
			spriteRenderer->SetBorderColor({ 1, 1, 0, 1.f });
			rigidbody = mCirclePlayer->CreateComponent<Rigidbody>(tempId++);
			 circleCo = mCirclePlayer->CreateComponent<CirclePlayerComponent>(tempId++);
			circleCo->SetSpped({ 100, 100 });
			rigidbody->SetMass(0);
			mCirclePlayer->SetParent(mBoxPlayer);
			mCirclePlayer->SetObjectType(eObjectType::Player);

			size = 10;
			for (size_t i = 0u; i < DUMMY_COUNT; ++i)
			{
				float x = 500 / DUMMY_COUNT * i - 500 * 0.5f;

				for (size_t j = 0u; j < DUMMY_COUNT; ++j)
				{
					float y = 300 / DUMMY_COUNT * j - 300 * 0.5f;;
					mDummy[i] = ObjectManager::GetInstance()->CreateObject(tempId++);
					mDummy[i]->SetObjectType(eObjectType::Enemy);
					transform = mDummy[i]->CreateComponent<Transform>(tempId++);
					transform->SetTranslate({ x,y });
					aabbCollider = mDummy[i]->CreateComponent<AABBCollider>(tempId++);
					aabbCollider->SetSize({ size, size });
					spriteRenderer = mDummy[i]->CreateComponent<SpriteRenderer>(tempId++);
					spriteRenderer->SetSize({ size, size });
					spriteRenderer->SetBaseColor({ 1, 0, 0, 0.5f });
					spriteRenderer->SetBorderColor({ 1, 0, 0, 1.f });
					rigidbody = mDummy[i]->CreateComponent<Rigidbody>(tempId++);

					rigidbody->SetMass(size);

					//rigidbody->AddVelocity({ rand() % 100 - 50.f,100 });
				}
			}
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