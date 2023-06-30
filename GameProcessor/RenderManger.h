#pragma once

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <string>
#include <map>

#include "Helper.h"
#include "AnimationAsset.h"
#include "AnimationInstance.h"
#include "Matrix3X3.h"

namespace gameProcessor
{
	class Circle;

	class RenderManager
	{
	public:
		RenderManager();
		~RenderManager() = default;

		void Init();
		void BeginDraw();
		void Clear(const Matrix3X3& matrix = gameProcessor::Matrix3X3::Identity(), D2D1_COLOR_F color = Helper::GetRGBA(255, 255, 255, 255));
		void EndDraw();
		void Release();

		void DrawLine(const Vector2& line, const Matrix3X3& matrix, D2D1_COLOR_F color = Helper::GetRGBA(0, 0, 0, 255));
		void DrawRectangle(const hRectangle& worldRect);
		void DrawRectangle(const hRectangle& worldRect, float radian, D2D1_COLOR_F color = Helper::GetRGBA(0, 0, 0, 255));
		void DrawRectangle(const hRectangle& localRect, const Matrix3X3& matrix, D2D1_COLOR_F color = Helper::GetRGBA(0, 0, 0, 255));
		void FillRectangle(const hRectangle& worldRect, float radian, D2D1_COLOR_F color = Helper::GetRGBA(0, 0, 0, 255));
		void FillRectangle(const hRectangle& localRect, const Matrix3X3& matrix, D2D1_COLOR_F color = Helper::GetRGBA(0, 0, 0, 255));
		void DrawCircle(const Circle& circle, const Matrix3X3& matrix, D2D1_COLOR_F color = Helper::GetRGBA(0, 0, 0, 255));
		void FillCircle(const Circle& circle, const Matrix3X3& matrix, D2D1_COLOR_F color = Helper::GetRGBA(0, 0, 0, 255));
		void DrawBitMap(const hRectangle& worldRect, const hRectangle& spriteRect, ID2D1Bitmap* bitmap);
		void DrawBitMap(const hRectangle& worldRect, const AnimationInstance& animationInstance);

		void WriteText(const hRectangle& rectangle, const std::wstring& text, unsigned int size, const Matrix3X3& matrix, D2D1_COLOR_F color = Helper::GetRGBA(0, 0, 0, 255));

		HRESULT CreateD2DBitmapFromFile(const WCHAR* imagePath);
		HRESULT CreateAnimationAsset(const WCHAR* imagePath, const std::vector<std::vector<hRectangle>>& frameInfo);

		inline ID2D1Bitmap* GetBitmapOrNull(const WCHAR* key);
		inline AnimationAsset* GetAnimationAssetOrNull(const WCHAR* key);

	private:
		HRESULT createDeviceResources(HWND hWnd);
		D2D1::Matrix3x2F convertMatrix(const Matrix3X3& matrix);

	private:
		ID2D1Factory* mFactory;
		ID2D1HwndRenderTarget* mRenderTarget;
		IWICImagingFactory* mWICFactory;
		IDWriteFactory* mWriteFactory;
		std::map<const WCHAR*, ID2D1Bitmap*> mBitmapMap;
		std::map<const WCHAR*, AnimationAsset*> mAnimationAssetMap;
	};

	ID2D1Bitmap* RenderManager::GetBitmapOrNull(const WCHAR* imangePath)
	{
		auto iter = mBitmapMap.find(imangePath);

		return iter == mBitmapMap.end() ? nullptr : iter->second;
	}

	inline AnimationAsset* RenderManager::GetAnimationAssetOrNull(const WCHAR* imangePath)
	{
		auto iter = mAnimationAssetMap.find(imangePath);

		return iter == mAnimationAssetMap.end() ? nullptr : iter->second;
	}
}