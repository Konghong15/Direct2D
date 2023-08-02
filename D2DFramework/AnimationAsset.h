#pragma once

#include "FrameInfomation.h"

#include <d2d1.h>
#include <vector>
#include <cassert>

namespace d2dFramework
{

	class AnimationAsset
	{
	public:
		AnimationAsset(ID2D1Bitmap* bitmap, const std::vector<std::vector<FrameInfomation>>& frameInfo);
		~AnimationAsset();
		AnimationAsset(const AnimationAsset& other) = delete;
		AnimationAsset& operator=(const AnimationAsset& other) = delete;

		inline ID2D1Bitmap* GetBitmap() const;
		inline const std::vector<std::vector<FrameInfomation>>& GetFrameInfomations() const;
		inline const FrameInfomation& GetFrameInfomation(unsigned int animationIndex, unsigned int frameIndex) const;
		inline unsigned int GetAnimationSize() const;
		inline unsigned int GetFrameSize(unsigned int animationIndex) const;

	private:
		ID2D1Bitmap* mBitmap;
		std::vector<std::vector<FrameInfomation>> mFrameInfomations;
	};

	ID2D1Bitmap* AnimationAsset::GetBitmap() const
	{
		return mBitmap;
	}
	const std::vector<std::vector<FrameInfomation>>& AnimationAsset::GetFrameInfomations() const
	{
		return mFrameInfomations;
	}
	const FrameInfomation& AnimationAsset::GetFrameInfomation(unsigned int animationIndex, unsigned int frameIndex) const
	{
		assert(animationIndex < GetAnimationSize());
		assert(frameIndex < GetFrameSize(animationIndex));
		return mFrameInfomations[animationIndex][frameIndex];
	}
	unsigned int AnimationAsset::GetAnimationSize() const
	{
		return mFrameInfomations.size();
	}
	unsigned int AnimationAsset::GetFrameSize(unsigned int animationIndex) const
	{
		assert(animationIndex < GetAnimationSize());
		return mFrameInfomations[animationIndex].size();
	}
}