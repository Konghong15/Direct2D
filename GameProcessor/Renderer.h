#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <dwrite.h>
#include <map>

#include "AnimationAsset.h"
#include "AnimationInstance.h"

namespace gameProcessor
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer() = default;

		void Init();
		void Release();

		void BeginDraw();
		void DrawBitMap(const hRectangle& worldRect, const hRectangle& spriteRect, const WCHAR* imageKey);
		void DrawBitMap(const hRectangle& worldRect, const AnimationInstance& animationInstance);
		void EndDraw();

		HRESULT CreateD2DBitmapFromFile(const WCHAR* imagePath);
		inline void AddAnimationAsset(const WCHAR* imagePath, AnimationAsset* anmationAsset);

		inline ID2D1Bitmap* GetBitmapOrNull(const WCHAR* imangePath);
		inline AnimationAsset* GetAnimationAssetOrNull(const WCHAR* imangePath);

	private:
		HRESULT createDeviceResources(HWND hWnd);

	private:
		ID2D1Factory* mFactory;
		ID2D1HwndRenderTarget* mRenderTarget;
		IWICImagingFactory* mWICFactory;
		std::map<const WCHAR*, ID2D1Bitmap*> mBitmapMap;
		std::map<const WCHAR*, AnimationAsset*> mAnimationAssetMap;
	};

	void Renderer::AddAnimationAsset(const WCHAR* imagePath, AnimationAsset* anmationAsset)
	{
		mAnimationAssetMap.emplace(imagePath, anmationAsset);
	}

	ID2D1Bitmap* Renderer::GetBitmapOrNull(const WCHAR* imangePath)
	{
		auto iter = mBitmapMap.find(imangePath);

		return iter == mBitmapMap.end() ? nullptr : iter->second;
	}

	inline AnimationAsset* Renderer::GetAnimationAssetOrNull(const WCHAR* imangePath)
	{
		auto iter = mAnimationAssetMap.find(imangePath);

		return iter == mAnimationAssetMap.end() ? nullptr : iter->second;
	}
}