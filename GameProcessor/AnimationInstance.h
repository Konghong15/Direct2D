#pragma once

namespace gameProcessor
{
	class RenderManager;
	class AnimationAsset;
	class hRectangle;
	class Matrix3X3;

	class AnimationInstance
	{
	public:
		AnimationInstance(const AnimationAsset& animationAssert, unsigned int animationIndex, unsigned int frameIndex, float progressTime, bool bLoop = true);

		void Update(float deltaTime);
		void Render(RenderManager* renderManager, const hRectangle& localRect, const Matrix3X3& matrix);

		void SetAnimationIndex(unsigned int index);
		void SetFrameIndex(unsigned int index);
		inline void SetProgressTime(float progressTime);
		inline void SetIsLoop(bool bLoop);

		unsigned int GetTotalFrameCount() const;
		inline const AnimationAsset& GetAnimaitionAsset() const;
		inline unsigned int GetAnimationindex() const;
		inline unsigned int GetFrameIndex() const;
		inline float GetProgressTime() const;
		inline bool GetIsLoop() const;
		inline bool GetIsEnd() const;
		inline void InitIsEnd();
		inline bool GetIsLastFrame() const;

	private:
		const AnimationAsset& mAnimationAsset; // 포인터와 동일, 안전한 포인터
		unsigned int mAnimationIndex;
		unsigned int mFrameIndex;
		float mProgressTime;
		float mElapsed;
		bool mbLoop;
		bool mbEnd;
		bool mbLastFrame;
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

	bool AnimationInstance::GetIsEnd() const
	{
		return mbEnd;
	}

	void AnimationInstance::InitIsEnd()
	{
		mbEnd = false;
	}

	bool AnimationInstance::GetIsLastFrame() const
	{
		return mbLastFrame;
	}
}