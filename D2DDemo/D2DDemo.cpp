#include "D2DDemo.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoxSprite.h"
#include "PlayerComponent.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "TempComponent.h"

#include "Circle.h"
#include "CircleCollider.h"
#include "CircleSprite.h"
#include "TempCircleComponent.h"
#include "Rigidbody.h"

namespace d2dDemo
{
	D2DDemo::D2DDemo(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mGameObject0(nullptr)
		, mGameObject1(nullptr)
	{
	}

	void D2DDemo::Init()
	{
		using namespace d2dFramework;

		GameProcessor::Init();
		mGameObject0 = new GameObject();
		Transform* transform0 = mGameObject0->CreateComponent<Transform>();
		transform0->SetTranslate({ 800, 500 });
		CircleSprite* sprite = mGameObject0->CreateComponent<CircleSprite>();
		sprite->SetEllipse({ {0, 0}, 100, 100 });
		sprite->SetBaseColor({ 0.5f, 0.f, 0.f, 0.5f });
		CircleCollider* boxCollider0 = mGameObject0->CreateComponent<CircleCollider>();
		mGameObject0->CreateComponent<Rigidbody>();

		/*mGameObject1 = new GameObject();
		Transform* transform1 = mGameObject1->CreateComponent<Transform>();
		transform1->SetTranslate({ 800, 500 });
		BoxSprite* boxSprite1 = mGameObject1->CreateComponent<BoxSprite>();
		boxSprite1->SetRectangle({ -50, -50, 50, 50 });
		boxSprite1->SetBaseColor({ 0.5f, 0.f, 0.f, 0.5f });
		BoxCollider* boxCollider1 = mGameObject1->CreateComponent<BoxCollider>();
		mGameObject1->CreateComponent<TempComponent>();*/

		mCircle = new GameObject();
		Transform* transform2 = mCircle->CreateComponent<Transform>();
		transform2->SetTranslate({ 1000, 500 });
		CircleSprite* circleSprite = mCircle->CreateComponent<CircleSprite>();
		circleSprite->SetEllipse({ {0, 0}, 100, 100 });
		circleSprite->SetBaseColor({ 0.5f, 0.f, 0.f, 0.5f });
		CircleCollider* circleCollider = mCircle->CreateComponent<CircleCollider>();
		mCircle->CreateComponent<TempCircleComponent>();

		const ColliderInfo& fo = boxCollider0->GetColliderInfo();

		ColliderInfo info;
		ZeroMemory(&info, sizeof(info));
		info.Size = { 100.f, 100.f };

		info.ColliderType = eColliderType::Circle;
		boxCollider0->SetColliderInfo(info);
		//info.ColliderType = eColliderType::AABB;
		//boxCollider1->SetColliderInfo(info);
		info.ColliderType = eColliderType::Circle;
		circleCollider->SetColliderInfo(info);
	}

	void D2DDemo::Update()
	{
		GameProcessor::Update();
	}

	void D2DDemo::Destroy()
	{
		delete mGameObject0;
		delete mGameObject1;

		GameProcessor::Destroy();
	}
}