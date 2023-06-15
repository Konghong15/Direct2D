#pragma once

#include <d2d1.h>

namespace gameProcessor
{
	class AnimationAsset;
	class hRectangle;

	class AnimationInstance
	{
	public:
		AnimationInstance(const AnimationAsset& animationAssert, unsigned int animationIndex, unsigned int frameIndex, float progressTime, bool bLoop = true);

		void Update(float deltaTime);

		void SetAnimationIndex(unsigned int index);
		void SetFrameIndex(unsigned int index);
		inline void SetProgressTime(float progressTime);
		inline void SetIsLoop(bool bLoop);

		inline const AnimationAsset& GetAnimaitionAsset() const;
		inline unsigned int GetAnimationindex() const;
		inline unsigned int GetFrameIndex() const;
		inline float GetProgressTime() const;
		inline bool GetIsLoop() const;

	private:
		const AnimationAsset& mAnimationAsset;
		unsigned int mAnimationIndex;
		unsigned int mFrameIndex;
		float mProgressTime;
		float mElapsed;
		bool mbLoop;
	};

	void AnimationInstance::SetProgressTime(float progressTime)
	{
		mProgressTime = progressTime;
	}

	void AnimationInstance::SetIsLoop(bool bLoop)
	{
		mbLoop = bLoop;
	}

	const AnimationAsset& AnimationInstance::GetAnimaitionAsset() const
	{
		return mAnimationAsset;
	}

	unsigned int AnimationInstance::GetFrameIndex() const
	{
		return mFrameIndex;
	}

	unsigned int AnimationInstance::GetAnimationindex() const
	{
		return mAnimationIndex;
	}

	float AnimationInstance::GetProgressTime() const
	{
		return mProgressTime;
	}

	bool AnimationInstance::GetIsLoop() const
	{
		return mbLoop;
	}
}