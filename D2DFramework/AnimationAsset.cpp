#include "AnimationAsset.h"

namespace d2dFramework
{
	AnimationAsset::AnimationAsset(ID2D1Bitmap* bitmap, const std::vector<std::vector<FrameInfomation>>& frameInfomations)
		: mBitmap(bitmap)
		, mFrameInfomations(frameInfomations)
	{
		int count = mBitmap->AddRef();
	}

	AnimationAsset::~AnimationAsset()
	{
		int count = mBitmap->Release();
		mBitmap = nullptr;
	}
}