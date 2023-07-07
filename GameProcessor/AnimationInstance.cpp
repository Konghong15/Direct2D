#include "AnimationInstance.h"
#include "AnimationAsset.h"
#include "hRectangle.h"
#include "RenderManger.h"

namespace gameProcessor
{
	AnimationInstance::AnimationInstance(const AnimationAsset& animationAsset, unsigned int animationIndex, unsigned int frameIndex, float progressTime, bool bLoop)
		: mAnimationAsset(animationAsset)
		, mFrameIndex(frameIndex)
		, mAnimationIndex(animationIndex)
		, mProgressTime(progressTime)
		, mElapsed(0.f)
		, mbLoop(bLoop)
		, mbEnd(false)
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
			if (mbLoop)
			{
				mFrameIndex = 0;
				mbEnd = true;
			}
			else
			{
				mFrameIndex = mFrameIndex - 1;
				mbEnd = true;
			}
		}
	}
	void AnimationInstance::Render(RenderManager* renderManager, const hRectangle& localRect, const Matrix3X3& matrix)
	{
		renderManager->DrawAnimationInstance(localRect, matrix, *this);
	}

	void AnimationInstance::SetFrameIndex(unsigned int index)
	{
		const unsigned int FRAME_SIZE = static_cast<unsigned int>(mAnimationAsset.GetFrameAnimationInfo().at(mAnimationIndex).size());

		if (FRAME_SIZE > index)
		{
			mFrameIndex = index;
		}
	}

	void AnimationInstance::SetAnimationIndex(unsigned int index)
	{
		const unsigned int ANIMATION_SIZE = static_cast<unsigned int>(mAnimationAsset.GetFrameAnimationInfo().size());

		if (ANIMATION_SIZE > index)
		{
			mAnimationIndex = index;
		}
	}
}