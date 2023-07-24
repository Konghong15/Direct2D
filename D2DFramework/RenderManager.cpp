#include <cassert>
#include <d2d1helper.h>
#include <comdef.h>

#include "RenderManger.h"
#include "WinApp.h"
#include "hRectangle.h"

#define DEFAULT_DPI 96.f

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

namespace d2dFramework
{
	RenderManager::RenderManager()
		: mFactory(nullptr)
		, mRenderTarget(nullptr)
		, mWICFactory(nullptr)
		, mTextFormat(nullptr)
	{
	}

	void RenderManager::Init()
	{
		HRESULT hr;

		hr = CoInitialize(NULL);
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mFactory);
		assert(SUCCEEDED(hr));

		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&mWICFactory)
		);
		assert(SUCCEEDED(hr));

		RECT rc;
		GetClientRect(d2dFramework::WinApp::GetHwnd(), &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			static_cast<UINT>(rc.right - rc.left),
			static_cast<UINT>(rc.bottom - rc.top)
		);
		hr = mFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(d2dFramework::WinApp::GetHwnd(), size),
			&mRenderTarget);
		assert(SUCCEEDED(hr));

		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&mWriteFactory));
		assert(SUCCEEDED(hr));

		SetWordSize(INIT_FONT_SIZE);
	}

	void RenderManager::Release()
	{
		mTextFormat->Release(); mTextFormat = nullptr;
		mFactory->Release(); mFactory = nullptr;
		mRenderTarget->Release(); mRenderTarget = nullptr;
		mWICFactory->Release(); mWICFactory = nullptr;
		mWriteFactory->Release(); mWriteFactory = nullptr;

		for (auto iter = mBitmapMap.begin(); iter != mBitmapMap.end(); ++iter)
		{
			ID2D1Bitmap* bitmap = iter->second;
			int count = bitmap->Release();
		}
		for (auto iter = mAnimationAssetMap.begin(); iter != mAnimationAssetMap.end(); ++iter)
		{
			AnimationAsset* animationAssert = iter->second;
			delete animationAssert;
		}

		mBitmapMap.clear();
		mAnimationAssetMap.clear();
	}

	void RenderManager::BeginDraw()
	{
		mRenderTarget->BeginDraw();
		mRenderTarget->Clear({ 255,255,255 });
		D2D1_SIZE_F rtSize = mRenderTarget->GetSize();
	}

	void RenderManager::Clear(D2D1::Matrix3x2F matrix, D2D1_COLOR_F color)
	{
		mRenderTarget->SetTransform(matrix);
		mRenderTarget->Clear(color);
		mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	void RenderManager::SetTransform(const D2D1::Matrix3x2F& trasform)
	{
		mRenderTarget->SetTransform(trasform);
	}

	void RenderManager::SetWordSize(unsigned int size)
	{
		if (mTextFormat != nullptr)
		{
			mTextFormat->Release();
			mTextFormat = nullptr;
		}

		HRESULT hr;
		hr = mWriteFactory->CreateTextFormat(L"Gulim", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL, size, L"ko-KR", &mTextFormat);
		assert(SUCCEEDED(hr));
	}

	void RenderManager::SetBrush()
	{
		ID2D1SolidColorBrush* brush = nullptr;
		HRESULT hr;
		hr = mRenderTarget->CreateSolidColorBrush(color, &brush);
		assert(SUCCEEDED(hr));
	}


	void RenderManager::DrawPoint(float x, float y, const D2D1::ColorF& color) {}

	void RenderManager::DrawPoint(const D2D1_POINT_2F& point, const D2D1::ColorF& color) {}


	void RenderManager::DrawLine(float x1, float y1, float x2, float y2, const D2D1::ColorF& color) {}

	void RenderManager::DrawLine(D2D1_POINT_2F start, D2D1_POINT_2F end, const D2D1::ColorF& color) {}


	void RenderManager::DrawCircle(float x, float y, float radiusX, float radiusY, const D2D1::ColorF& color) {}

	void RenderManager::DrawCircle(const D2D1_ELLIPSE& ellipse, const D2D1::ColorF& color) {}

	void RenderManager::FillCircle(float x, float y, float radiusX, float radiusY, const D2D1::ColorF& color) {}

	void RenderManager::FillCircle(const D2D1_ELLIPSE& ellipse, const D2D1::ColorF& color) {}


	void RenderManager::DrawFillRectangle(float left, float top, float right, float bottom, const D2D1::ColorF& color) {}

	void RenderManager::DrawFillRectangle(const D2D1_RECT_F& rectangle, const D2D1::ColorF& color) {}

	void RenderManager::DrawRectangle(float left, float top, float right, float bottom, const D2D1::ColorF& color) {}

	void RenderManager::DrawRectangle(const D2D1_RECT_F& rectangle, const D2D1::ColorF& color) {}

	{}

	void RenderManager::DrawPolygon(std::vector<D2D1_POINT_2F>& pointList, const D2D1::ColorF& color) {}

	void RenderManager::DrawGrid(float x, float y, float width, float height, float interval, const D2D1::ColorF& color) {}


	void RenderManager::DrawBitMap(const hRectangle& localRect, const hRectangle& spriteRect, ID2D1Bitmap* bitmap) {}


	void RenderManager::WriteText(const wchar_t* text, float left, float top, float width, float height, const D2D1::ColorF& color) {}

	void RenderManager::WriteText(const wchar_t* text, const D2D1_RECT_F& rectangle, const D2D1::ColorF& color) {}



	void RenderManager::DrawLine(const Vector2& line, const Matrix3X3& matrix, D2D1_COLOR_F color)
	{
		ID2D1SolidColorBrush* brush;
		HRESULT hr = mRenderTarget->CreateSolidColorBrush(color, &brush);
		assert(SUCCEEDED(hr));

		{
			mRenderTarget->SetTransform(convertMatrix(matrix));
			mRenderTarget->DrawLine({ 0,0 }, { line.GetX(), line.GetY() }, brush, 5.f);
			mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		}

		brush->Release();
	}

	void RenderManager::DrawRectangle(const hRectangle& worldRect)
	{
		D2D1_POINT_2F vertices[3] = {
			{ worldRect.GetTopLeft().GetX(), worldRect.GetTopLeft().GetY() },
			{ worldRect.GetTopRight().GetX(), worldRect.GetTopRight().GetY() },
			{ worldRect.GetBottomLeft().GetX(), worldRect.GetBottomLeft().GetY() }
		};

		//ID2D1PathGeometry* pPathGeometry;
		//pFactory->CreatePathGeometry(&pPathGeometry);

		//ID2D1GeometrySink* pGeometrySink;
		//pPathGeometry->Open(&pGeometrySink);

		//pGeometrySink->BeginFigure(vertices[0], D2D1_FIGURE_BEGIN_FILLED);
		//pGeometrySink->AddLines(vertices.data() + 1, vertices.size() - 1);
		//pGeometrySink->EndFigure(D2D1_FIGURE_END_CLOSED);
		//pGeometrySink->Close();

		//pRenderTarget->DrawGeometry(pPathGeometry, pBrush);  // pBrush는 브러시 객체입니다.

		//pGeometrySink->Release();
		//pPathGeometry->Release();
	}

	void RenderManager::DrawRectangle(const hRectangle& worldRect, float radian, D2D1_COLOR_F color)
	{
		const Vector2& TL = worldRect.GetTopLeft();
		const Vector2& BR = worldRect.GetBottomRight();
		const Vector2& CENTER = worldRect.GetCenter();
		ID2D1SolidColorBrush* brush;
		HRESULT hr = mRenderTarget->CreateSolidColorBrush(color, &brush);
		assert(SUCCEEDED(hr));

		mRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(Helper::RadianToDegree(radian), { CENTER.GetX(), CENTER.GetY() }));
		mRenderTarget->DrawRecta ngle({ TL.GetX(), TL.GetY(), BR.GetX(), BR.GetY() }, brush, 5.f);
		mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		brush->Release();
	}

	void RenderManager::DrawRectangle(const hRectangle& localRect, const Matrix3X3& matrix, D2D1_COLOR_F color)
	{
		const Vector2& TL = localRect.GetTopLeft();
		const Vector2& BR = localRect.GetBottomRight();
		const Vector2& CENTER = localRect.GetCenter();
		ID2D1SolidColorBrush* brush;
		HRESULT hr = mRenderTarget->CreateSolidColorBrush(color, &brush);
		assert(SUCCEEDED(hr));

		mRenderTarget->SetTransform(convertMatrix(matrix));
		mRenderTarget->DrawRectangle({ TL.GetX(), TL.GetY(), BR.GetX(), BR.GetY() }, brush, 5.f);
		mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		brush->Release();
	}

	void RenderManager::FillRectangle(const hRectangle& worldRect, float radian, D2D1_COLOR_F color)
	{
		const Vector2& TL = worldRect.GetTopLeft();
		const Vector2& BR = worldRect.GetBottomRight();
		const Vector2& CENTER = worldRect.GetCenter();
		ID2D1SolidColorBrush* brush;
		HRESULT hr = mRenderTarget->CreateSolidColorBrush(color, &brush);
		assert(SUCCEEDED(hr));

		mRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(Helper::RadianToDegree(radian), { CENTER.GetX(), CENTER.GetY() }));
		mRenderTarget->FillRectangle({ TL.GetX(), TL.GetY(), BR.GetX(), BR.GetY() }, brush);
		mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		brush->Release();
	}

	void RenderManager::FillRectangle(const hRectangle& localRect, const Matrix3X3& matrix, D2D1_COLOR_F color)
	{
		ID2D1SolidColorBrush* brush;
		HRESULT hr = mRenderTarget->CreateSolidColorBrush(color, &brush);
		assert(SUCCEEDED(hr));

		const Vector2& TL = localRect.GetTopLeft();
		const Vector2& BR = localRect.GetBottomRight();
		const Vector2& CENTER = localRect.GetCenter();

		mRenderTarget->SetTransform(convertMatrix(matrix));
		mRenderTarget->FillRectangle({ TL.GetX(), TL.GetY(), BR.GetX(), BR.GetY() }, brush);
		mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		brush->Release();
	}

	void RenderManager::DrawCircle(const Circle& circle, const Matrix3X3& matrix, D2D1_COLOR_F color)
	{
		ID2D1SolidColorBrush* brush;
		HRESULT hr = mRenderTarget->CreateSolidColorBrush(color, &brush);
		assert(SUCCEEDED(hr));

		const Vector2& center = circle.GetCenter();
		float radius = circle.GetRadius();

		mRenderTarget->SetTransform(convertMatrix(matrix));
		D2D1_ELLIPSE ellipse = D2D1::Ellipse({ center.GetX(), center.GetY() }, radius, radius);
		mRenderTarget->DrawEllipse(ellipse, brush, 5.0f);
		mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		brush->Release();
	}

	void RenderManager::FillCircle(const Circle& circle, const Matrix3X3& matrix, D2D1_COLOR_F color)
	{
		ID2D1SolidColorBrush* brush;
		HRESULT hr = mRenderTarget->CreateSolidColorBrush(color, &brush);
		assert(SUCCEEDED(hr));

		const Vector2& center = circle.GetCenter();
		float radius = circle.GetRadius();

		mRenderTarget->SetTransform(convertMatrix(matrix));
		D2D1_ELLIPSE ellipse = D2D1::Ellipse({ center.GetX(), center.GetY() }, radius, radius);
		mRenderTarget->FillEllipse(ellipse, brush);
		mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		brush->Release();
	}

	void RenderManager::DrawBitMap(const hRectangle& localRect, const hRectangle& spriteRect, const Matrix3X3& matrix, ID2D1Bitmap* bitmap)
	{
		const Vector2& WORLD_TL = localRect.GetTopLeft();
		const Vector2& WORLD_BR = localRect.GetBottomRight();

		const Vector2& SPRITE_TL = spriteRect.GetTopLeft();
		const Vector2& SPRITE_BR = spriteRect.GetBottomRight();

		mRenderTarget->SetTransform(convertMatrix(matrix));
		mRenderTarget->DrawBitmap(bitmap
			, D2D1::RectF(WORLD_TL.GetX(), WORLD_TL.GetY(), WORLD_BR.GetX(), WORLD_BR.GetY())
			, 1.0f
			, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
			, D2D1::RectF(SPRITE_TL.GetX(), SPRITE_TL.GetY(), SPRITE_BR.GetX(), SPRITE_BR.GetY()));
		mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	void RenderManager::DrawAnimationInstance(const hRectangle& localRect, const Matrix3X3& matrix, const AnimationInstance& animationInstance)
	{
		const AnimationAsset& animationAsset = animationInstance.GetAnimaitionAsset();
		const unsigned int FRAME_INDEX = animationInstance.GetFrameIndex();
		const unsigned int ANIMATION_INDEX = animationInstance.GetAnimationindex();

		const hRectangle& SPRITE_RECT = animationAsset.GetFrameAnimationInfo().at(ANIMATION_INDEX).at(FRAME_INDEX);
		DrawBitMap(localRect, SPRITE_RECT, matrix, animationAsset.GetBitmap());
	}

	void RenderManager::WriteText(const hRectangle& rectangle, const std::wstring& text, unsigned int size, const Matrix3X3& matrix, D2D1_COLOR_F color)
	{
		IDWriteTextFormat* textFormat = nullptr;
		ID2D1SolidColorBrush* brush = nullptr;
		HRESULT hr;
		hr = mWriteFactory->CreateTextFormat(L"Gulim", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL, size, L"ko-KR", &textFormat);
		assert(SUCCEEDED(hr));
		hr = mRenderTarget->CreateSolidColorBrush(color, &brush);
		assert(SUCCEEDED(hr));

		const Vector2& TL = rectangle.GetTopLeft();
		const Vector2& BR = rectangle.GetBottomRight();
		mRenderTarget->SetTransform(convertMatrix(matrix));
		mRenderTarget->DrawText(text.c_str(), text.length(), textFormat, { TL.GetX(), TL.GetY(), BR.GetX(), BR.GetY() }, brush);

		textFormat->Release();
		brush->Release();
	}

	void RenderManager::EndDraw()
	{
		mRenderTarget->EndDraw();
	}

	HRESULT RenderManager::CreateD2DBitmapFromFile(const WCHAR* filePath)
	{
		auto iter = mBitmapMap.find(filePath);

		if (iter != mBitmapMap.end())
		{
			return S_FALSE;
		}

		HRESULT hr = S_OK;
		IWICBitmapDecoder* decoder = nullptr;
		IWICBitmapFrameDecode* frameDecode = nullptr;
		IWICFormatConverter* convertedBitmap = nullptr;
		ID2D1Bitmap* bitmap = nullptr;

		// 디코더 생성
		hr = mWICFactory->CreateDecoderFromFilename(filePath, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
		if (FAILED(hr)) { goto END; }

		// 프레임 디코더를 통해 0번쨰 프레임 얻기 (압축파일을 메모리의 비트맵으로 사용하기 위해)
		hr = decoder->GetFrame(0, &frameDecode);
		if (FAILED(hr)) { goto END; }

		// 32비트맵 픽셀 포멧으로 변경하기 위해 컨버터 생성
		hr = mWICFactory->CreateFormatConverter(&convertedBitmap);
		if (FAILED(hr)) { goto END; }

		// 32비트맵 픽셀 포멧으로 변경
		hr = convertedBitmap->Initialize(frameDecode, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeCustom);
		if (FAILED(hr)) { goto END; }

		// 렌더타겟 체크
		hr = createDeviceResources(gameProcessor::WinApp::GetHwnd());
		if (FAILED(hr)) { goto END; }

		hr = mRenderTarget->CreateBitmapFromWicBitmap(convertedBitmap, NULL, &bitmap);
		if (FAILED(hr)) { goto END; }
		mBitmapMap.emplace(filePath, bitmap);

	END:
		if (decoder != nullptr)
		{
			decoder->Release();
		}
		if (frameDecode != nullptr)
		{
			frameDecode->Release();
		}
		if (convertedBitmap != nullptr)
		{
			convertedBitmap->Release();
		}
		if (FAILED(hr))
		{
			_com_error err(hr);
			MessageBox(gameProcessor::WinApp::GetHwnd(), filePath, L"비트맵 로드 에러", MB_OK);
		}

		return hr;
	}

	HRESULT RenderManager::CreateD2DBitmapFromFile(const WCHAR* key, const WCHAR* filePath)
	{
		auto iter = mBitmapMap.find(key);

		if (iter != mBitmapMap.end())
		{
			return S_FALSE;
		}

		HRESULT hr = S_OK;
		IWICBitmapDecoder* decoder = nullptr;
		IWICBitmapFrameDecode* frameDecode = nullptr;
		IWICFormatConverter* convertedBitmap = nullptr;
		ID2D1Bitmap* bitmap = nullptr;

		// 디코더 생성
		hr = mWICFactory->CreateDecoderFromFilename(filePath, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
		if (FAILED(hr)) { goto END; }

		// 프레임 디코더를 통해 0번쨰 프레임 얻기 (압축파일을 메모리의 비트맵으로 사용하기 위해)
		hr = decoder->GetFrame(0, &frameDecode);
		if (FAILED(hr)) { goto END; }

		// 32비트맵 픽셀 포멧으로 변경하기 위해 컨버터 생성
		hr = mWICFactory->CreateFormatConverter(&convertedBitmap);
		if (FAILED(hr)) { goto END; }

		// 32비트맵 픽셀 포멧으로 변경
		hr = convertedBitmap->Initialize(frameDecode, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeCustom);
		if (FAILED(hr)) { goto END; }

		// 렌더타겟 체크
		hr = createDeviceResources(gameProcessor::WinApp::GetHwnd());
		if (FAILED(hr)) { goto END; }

		hr = mRenderTarget->CreateBitmapFromWicBitmap(convertedBitmap, NULL, &bitmap);
		if (FAILED(hr)) { goto END; }
		mBitmapMap.emplace(key, bitmap);

	END:
		if (decoder != nullptr)
		{
			decoder->Release();
		}
		if (frameDecode != nullptr)
		{
			frameDecode->Release();
		}
		if (convertedBitmap != nullptr)
		{
			convertedBitmap->Release();
		}
		if (FAILED(hr))
		{
			_com_error err(hr);
			MessageBox(gameProcessor::WinApp::GetHwnd(), filePath, L"비트맵 로드 에러", MB_OK);
		}

		return hr;
	}

	HRESULT RenderManager::CreateAnimationAsset(const WCHAR* imagePath, const std::vector<std::vector<hRectangle>>& frameInfo)
	{
		auto iter = mAnimationAssetMap.find(imagePath);

		if (iter != mAnimationAssetMap.end())
		{
			return S_FALSE;
		}

		ID2D1Bitmap* bitmap = GetBitmapOrNull(imagePath);

		if (bitmap == nullptr)
		{
			if (FAILED(CreateD2DBitmapFromFile(imagePath)))
			{
				return E_FAIL;
			}
		}

		bitmap = GetBitmapOrNull(imagePath);
		assert(bitmap != nullptr);
		mAnimationAssetMap.emplace(imagePath, new AnimationAsset(bitmap, frameInfo));
	}

	HRESULT RenderManager::CreateAnimationAsset(const WCHAR* key, const WCHAR* imagePath, const std::vector<std::vector<hRectangle>>& frameInfo)
	{
		auto iter = mAnimationAssetMap.find(key);

		if (iter != mAnimationAssetMap.end())
		{
			return S_FALSE;
		}

		ID2D1Bitmap* bitmap = GetBitmapOrNull(key);

		if (bitmap == nullptr)
		{
			if (FAILED(CreateD2DBitmapFromFile(key, imagePath)))
			{
				return E_FAIL;
			}
		}

		bitmap = GetBitmapOrNull(key);
		assert(bitmap != nullptr);
		mAnimationAssetMap.emplace(key, new AnimationAsset(bitmap, frameInfo));
	}

	HRESULT RenderManager::createDeviceResources(HWND hWnd)
	{
		HRESULT hr = S_OK;

		if (!mRenderTarget)
		{
			RECT rc;
			hr = GetClientRect(hWnd, &rc) ? S_OK : E_FAIL;

			if (SUCCEEDED(hr))
			{
				// Create a D2D render target properties
				D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties = D2D1::RenderTargetProperties();

				// Set the DPI to be the default system DPI to allow direct mapping
				// between image pixels and desktop pixels in different system DPI settings
				renderTargetProperties.dpiX = DEFAULT_DPI;
				renderTargetProperties.dpiY = DEFAULT_DPI;

				// Create a D2D render target
				D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

				hr = mFactory->CreateHwndRenderTarget(
					renderTargetProperties,
					D2D1::HwndRenderTargetProperties(hWnd, size),
					&mRenderTarget
				);
			}
		}

		return hr;
	}

	D2D1::Matrix3x2F RenderManager::convertMatrix(const Matrix3X3& matrix)
	{
		D2D1::Matrix3x2F result;

		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				result.m[j][i] = matrix.GetValue(i, j);
			}
		}

		return result;
	}
}