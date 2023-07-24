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

		SetFontSize(INIT_FONT_SIZE);
		SetColor({ 0.f,0.f,0.f,1.f });
		SetStrokeWidth(1.f);
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

	void RenderManager::EndDraw()
	{
		mRenderTarget->EndDraw();
	}

	void RenderManager::SetTransform(const D2D1::Matrix3x2F& trasform)
	{
		mRenderTarget->SetTransform(trasform);
	}

	void RenderManager::SetFontSize(unsigned int size)
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

	D2D1_COLOR_F RenderManager::SetColor(const D2D1_COLOR_F& color)
	{
		if (mBrush != nullptr)
		{
			D2D1_COLOR_F before = mBrush->GetColor();
			mBrush->SetColor(color);

			return before;
		}

		HRESULT hr = mRenderTarget->CreateSolidColorBrush(color, &mBrush);
		assert(SUCCEEDED(hr));

		return mBrush->GetColor()
	}

	void RenderManager::SetStrokeWidth(float strokeWidth)
	{
		mStrokeWidth = strokeWidth;
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