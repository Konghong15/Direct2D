#include "CircleSprite.h"
#include "GameObject.h"
#include "Transform.h"
#include "RenderManger.h"

namespace d2dFramework
{
	CircleSprite::CircleSprite(GameObject* owner)
		: Component(owner)
		, mEllipse{ { 0.f, 0.f}, 10.f, 10.f }
		, mBaseColor{ 1.f, 1.f, 1.f, 1.f }
		, mBorderColor{ 0.f, 0.f, 0.f, 1.f }
	{
	}

	void CircleSprite::Render(RenderManager* renderManager)
	{
		Transform* transform = GetGameObject()->GetComponent<Transform>();
		D2D1::Matrix3x2F matrix = transform->GetTransform();

		D2D1_COLOR_F prevColor = renderManager->SetColor(mBorderColor);
		renderManager->SetTransform(matrix);
		{
			renderManager->DrawCircle(mEllipse);
			renderManager->SetColor(mBaseColor);
			renderManager->FillCircle(mEllipse);
		}
		renderManager->SetTransform(D2D1::Matrix3x2F::Identity());
		renderManager->SetColor(prevColor);

	}
};
