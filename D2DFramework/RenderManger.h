#pragma once

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <string>
#include <map>
#include <vector>

namespace d2dFramework
{
	class Vector2;
	class AnimationAsset;

	class RenderManager
	{
	public:
		RenderManager();
		~RenderManager() = default;

		void Init();
		void BeginDraw();
		void Clear(D2D1::Matrix3x2F matrix = D2D1::Matrix3x2F::Identity(), D2D1_COLOR_F color = { 1.f, 1.f, 1.f, 1.f });
		void EndDraw();
		void Release();

		void DrawPoint(float x, float y);
		void DrawPoint(const D2D1_POINT_2F& point);

		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawLine(D2D1_POINT_2F start, D2D1_POINT_2F end);

		void DrawCircle(float x, float y, float radiusX, float radiusY);
		void DrawCircle(const D2D1_ELLIPSE& ellipse);
		void FillCircle(float x, float y, float radiusX, float radiusY);
		void FillCircle(const D2D1_ELLIPSE& ellipse);

		void DrawFillRectangle(float left, float top, float right, float bottom);
		void DrawFillRectangle(const D2D1_RECT_F& rectangle);
		void DrawRectangle(float left, float top, float right, float bottom);
		void DrawRectangle(const D2D1_RECT_F& rectangle);

		void DrawPolygon(std::vector<D2D1_POINT_2F>& pointList);
		void DrawGrid(float x, float y, float width, float height, float interval);

		void DrawBitMap(float left, float top, float right, float bottom, float uvLeft, float uvTop, float uvRight, float uvBottom, ID2D1Bitmap* bitmap);
		void DrawBitMap(const D2D1_RECT_F& rectangle, const D2D1_RECT_F& uvRectangle, ID2D1Bitmap* bitmap);

		void WriteText(const wchar_t* text, float left, float top, float width, float height);
		void WriteText(const wchar_t* text, const D2D1_RECT_F& rectangle);

		HRESULT CreateD2DBitmapFromFile(const WCHAR* imagePath);
		HRESULT CreateD2DBitmapFromFile(const WCHAR* key, const WCHAR* imagePath);
		HRESULT CreateAnimationAsset(const WCHAR* imagePath, const std::vector<std::vector<hRectangle>>& frameInfo);
		HRESULT CreateAnimationAsset(const WCHAR* key, const WCHAR* imagePath, const std::vector<std::vector<hRectangle>>& frameInfo);

		void SetTransform(const D2D1::Matrix3x2F& trasform);
		void SetFontSize(unsigned int fontSize);
		D2D1_COLOR_F SetColor(const D2D1_COLOR_F& color);
		void SetStrokeWidth(float strokeWidth);

		inline ID2D1Bitmap* GetBitmapOrNull(const WCHAR* key);
		inline AnimationAsset* GetAnimationAssetOrNull(const WCHAR* key);

	private:
		HRESULT createDeviceResources(HWND hWnd);

	private:
		enum { INIT_FONT_SIZE = 15 };

		ID2D1Factory* mFactory;
		ID2D1HwndRenderTarget* mRenderTarget;
		IWICImagingFactory* mWICFactory;
		IDWriteFactory* mWriteFactory;

		IDWriteTextFormat* mTextFormat;
		ID2D1SolidColorBrush* mBrush;
		float mStrokeWidth;
		D2D1::ColorF mBeforeColor;
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