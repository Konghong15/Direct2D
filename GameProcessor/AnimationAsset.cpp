#include "AnimationAsset.h"

namespace gameProcessor
{
	AnimationAsset::AnimationAsset(ID2D1Bitmap* bitmap, const std::vector<std::vector<hRectangle>>& frameAnimationInfo)
		: mBitmap(bitmap)
		, mFrameAnimaitonInfo(frameAnimationInfo)
	{
		int count = mBitmap->AddRef();
	}

	AnimationAsset::~AnimationAsset()
	{
		int count = mBitmap->Release();
		mBitmap = nullptr;
	}
}