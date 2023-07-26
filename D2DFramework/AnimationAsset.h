#pragma once

#include <d2d1.h>
#include <vector>

#include "hRectangle.h"

namespace d2dFramework
{
	class AnimationAsset
	{
	public:
		AnimationAsset(ID2D1Bitmap* bitmap, const std::vector<std::vector<hRectangle>>& frameInfo);
		~AnimationAsset();
		AnimationAsset(const AnimationAsset& other) = delete;
		AnimationAsset& operator=(const AnimationAsset& other) = delete;

		inline ID2D1Bitmap* GetBitmap() const;
		inline const std::vector<std::vector<hRectangle>>& GetFrameAnimationInfo() const;

	private:
		ID2D1Bitmap* mBitmap;
		std::vector<std::vector<hRectangle>> mFrameAnimaitonInfo;
	};

	ID2D1Bitmap* AnimationAsset::GetBitmap() const
	{
		return mBitmap;
	}

	const std::vector<std::vector<hRectangle>>& AnimationAsset::GetFrameAnimationInfo() const
	{
		return mFrameAnimaitonInfo;
	}
}