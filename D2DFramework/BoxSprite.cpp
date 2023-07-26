#include "BoxSprite.h"
#include "GameObject.h"
#include "Transform.h"
#include "RenderManger.h"

namespace d2dFramework
{
	BoxSprite::BoxSprite(GameObject* owner)
		: Component(owner)
		, mRectangle{ -10, 10, 10, -10 }
		, mBaseColor{ 1.f, 1.f, 1.f, 1.f }
		, mBorderColor{ 0.f, 0.f, 0.f, 1.f }
	{
	}

	void BoxSprite::Render(RenderManager* renderManager)
	{
		Transform* transform = GetGameObject()->GetComponent<Transform>();
		D2D1::Matrix3x2F matrix = transform->GetTransform();

		D2D1_COLOR_F prevColor = renderManager->SetColor(mBorderColor);
		renderManager->SetTransform(matrix);
		{
			renderManager->DrawRectangle(mRectangle);
			renderManager->SetColor(mBaseColor);
			renderManager->FillRectangle(mRectangle);
		}
		renderManager->SetTransform(D2D1::Matrix3x2F::Identity());
		renderManager->SetColor(prevColor);

	}
};
