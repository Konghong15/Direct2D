#include "D2DDemo.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoxSprite.h"
#include "PlayerComponent.h"

namespace d2dDemo
{
	D2DDemo::D2DDemo(UINT width, UINT height, std::wstring name)
		: GameProcessor(width, height, name)
		, mGameObject(nullptr)
	{
	}

	void D2DDemo::Init()
	{
		using namespace d2dFramework;

		GameProcessor::Init();
		mGameObject = new GameObject();
		Transform* transform = mGameObject->CreateComponent<Transform>();
		transform->SetTranslate({ 800, 500 });
		BoxSprite* boxSprite = mGameObject->CreateComponent<BoxSprite>();
		boxSprite->SetRectangle({ -100, -100, 100, 100 });
		boxSprite->SetBaseColor({ 0.5f, 0.f, 0.f, 0.5f });
		PlayerComponent* playerComponent = mGameObject->CreateComponent<PlayerComponent>();

	}

	void D2DDemo::Update()
	{
		GameProcessor::Update();
	}

	void D2DDemo::Destroy()
	{
		delete mGameObject;

		GameProcessor::Destroy();
	}
}