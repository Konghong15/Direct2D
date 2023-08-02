#include "AnimationRenderer.h"

#include "AnimationAsset.h"
#include "GameObject.h"
#include "Transform.h"
#include "RenderManger.h"
#include "EventManager.h"

#include <cassert>

namespace d2dFramework
{
	AnimationRenderer::AnimationRenderer(unsigned int id, GameObject* owner)
		: Component(id, owner)
		, mbIsLoop(false)
	{
	}

	void AnimationRenderer::Init()
	{
		IRenderable::Init();
		IUpdateable::Init();
	}

	void AnimationRenderer::Update(float deltaTime)
	{
		mAccumulatedTime += deltaTime;

		FrameInfomation current = mAnimationAsset->GetFrameInfomation(mAnimationIndex, mFrameIndex);
		while (mAccumulatedTime >= current.AnimationTime)
		{
			++mFrameIndex;

			if (mFrameIndex == mAnimationAsset->GetFrameSize(mAnimationIndex))
			{
				if (mbIsLoop)
				{
					mFrameIndex = 0;
				}
				else
				{
					--mFrameIndex;
				}

				EventManager::GetInstance()->SendEvent("AnimationEnd", BaseEntity::GetId(), "");
			}

			mAccumulatedTime -= current.AnimationTime;
			current = mAnimationAsset->GetFrameInfomation(mAnimationIndex, mFrameIndex);
		}
	}

	void AnimationRenderer::Render()
	{
		Transform* transform = GetGameObject()->GetComponent<Transform>();
		D2D1::Matrix3x2F matrix = transform->GetTransform();
		GetRenderManager()->SetTransform(matrix);
		{
			const FrameInfomation& frameInfo = mAnimationAsset->GetFrameInfomation(mAnimationIndex, mFrameIndex);
			GetRenderManager()->DrawBitMap(mOffset, mSize, frameInfo.UVRectangle, mAnimationAsset->GetBitmap());
		}
		GetRenderManager()->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	void AnimationRenderer::Release()
	{
		IRenderable::Release();
		IUpdateable::Release();
	}
}