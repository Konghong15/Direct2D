#include "AnimationInstance.h"
#include "AnimationAsset.h"
#include "hRectangle.h"

namespace gameProcessor
{
	AnimationInstance::AnimationInstance(const AnimationAsset& animationAsset, unsigned int animationIndex, unsigned int frameIndex, float progressTime, bool bLoop)
		: mAnimationAsset(animationAsset)
		, mFrameIndex(frameIndex)
		, mAnimationIndex(animationIndex)
		, mProgressTime(progressTime)
		, mElapsed(0.f)
		, mbLoop(bLoop)
	{
	}

	void AnimationInstance::Update(float deltaTime)
	{
		mElapsed += deltaTime;

		if (mElapsed >= mProgressTime)
		{
			mElapsed -= mProgressTime;

			++mFrameIndex;
		}

		const unsigned int FRAME_SIZE = static_cast<unsigned int>(mAnimationAsset.GetFrameAnimationInfo().at(mAnimationIndex).size());

		if (FRAME_SIZE <= mFrameIndex)
		{
			mFrameIndex = mbLoop ? 0 : mFrameIndex - 1;
		}
	}

	//void AnimationInstance::Render(const hRectangle& worldRect, ID2D1HwndRenderTarget* renderTarget)
	//{
	//	const Vector2& WORLD_TL = worldRect.GetTopLeft();
	//	const Vector2& WORLD_BR = worldRect.GetBottomRight();

	//	const hRectangle rect = mAnimationAsset.GetFrameAnimationInfo().at(mFrameIndex).at(mAnimationIndex);
	//	const Vector2& TL = rect.GetTopLeft();
	//	const Vector2& BR = rect.GetBottomRight();

	//	renderTarget->DrawBitmap(mAnimationAsset.GetBitmap()
	//		, D2D1::RectF(WORLD_TL.GetX(), WORLD_TL.GetY(), WORLD_BR.GetX(), WORLD_BR.GetY())
	//		, 1.0f
	//		, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
	//		, D2D1::RectF(TL.GetX(), TL.GetY(), BR.GetX(), BR.GetY()));
	//}

	void AnimationInstance::SetFrameIndex(unsigned int index)
	{
		const unsigned int FRAME_SIZE = static_cast<unsigned int>(mAnimationAsset.GetFrameAnimationInfo().size());
		mFrameIndex += FRAME_SIZE > index ? index : mFrameIndex;
	}

	void AnimationInstance::SetAnimationIndex(unsigned int index)
	{
		const unsigned int ANIMATION_SIZE = static_cast<unsigned int>(mAnimationAsset.GetFrameAnimationInfo().at(mFrameIndex).size());
		mAnimationIndex += ANIMATION_SIZE > index ? index : mAnimationIndex;
	}
}