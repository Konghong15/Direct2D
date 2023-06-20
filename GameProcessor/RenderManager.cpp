#include <cassert>
#include <d2d1helper.h>
#include <comdef.h>

#include "RenderManger.h"
#include "WinApp.h"
#include "hRectangle.h"

#define DEFAULT_DPI 96.f

namespace gameProcessor
{
	RenderManager::RenderManager()
		: mFactory(nullptr)
		, mRenderTarget(nullptr)
		, mWICFactory(nullptr)
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
		GetClientRect(gameProcessor::WinApp::GetHwnd(), &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			static_cast<UINT>(rc.right - rc.left),
			static_cast<UINT>(rc.bottom - rc.top)
		);
		hr = mFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(gameProcessor::WinApp::GetHwnd(), size),
			&mRenderTarget);
		assert(SUCCEEDED(hr));
	}

	void RenderManager::Release()
	{
		mFactory->Release();
		mRenderTarget->Release();
		mWICFactory->Release();

		for (auto iter = mBitmapMap.begin(); iter != mBitmapMap.end(); ++iter)
		{
			ID2D1Bitmap* bitmap = iter->second;
			bitmap->Release();
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
	}

	void RenderManager::DrawRectangle(const hRectangle& worldRect)
	{
		mRenderTarget->DrawRectangle();
	}

	void RenderManager::DrawCircle(const Circle& circle)
	{

	}

	void RenderManager::DrawBitMap(const hRectangle& worldRect, const hRectangle& spriteRect, ID2D1Bitmap* bitmap)
	{
		const Vector2& WORLD_TL = worldRect.GetTopLeft();
		const Vector2& WORLD_BR = worldRect.GetBottomRight();

		const Vector2& SPRITE_TL = spriteRect.GetTopLeft();
		const Vector2& SPRITE_BR = spriteRect.GetBottomRight();

		mRenderTarget->DrawBitmap(bitmap
			, D2D1::RectF(WORLD_TL.GetX(), WORLD_TL.GetY(), WORLD_BR.GetX(), WORLD_BR.GetY())
			, 1.0f
			, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
			, D2D1::RectF(SPRITE_TL.GetX(), SPRITE_TL.GetY(), SPRITE_BR.GetX(), SPRITE_BR.GetY()));
	}

	void RenderManager::DrawBitMap(const hRectangle& worldRect, const AnimationInstance& animationInstance)
	{
		const AnimationAsset& animationAsset = animationInstance.GetAnimaitionAsset();
		const unsigned int FRAME_INDEX = animationInstance.GetFrameIndex();
		const unsigned int ANIMATION_INDEX = animationInstance.GetAnimationindex();

		const hRectangle& SPRITE_RECT = animationAsset.GetFrameAnimationInfo().at(ANIMATION_INDEX).at(FRAME_INDEX);
		DrawBitMap(worldRect, SPRITE_RECT, animationAsset.GetBitmap());
	}

	void RenderManager::EndDraw()
	{
		mRenderTarget->EndDraw();
	}

	HRESULT RenderManager::CreateD2DBitmapFromFile(const WCHAR* filePath)
	{
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

	HRESULT RenderManager::CreateAnimationAsset(const WCHAR* imagePath, const std::vector<std::vector<hRectangle>>& frameInfo)
	{
		ID2D1Bitmap* bitmap = GetBitmapOrNull(imagePath);

		if (bitmap == nullptr)
		{
			if (FAILED(CreateD2DBitmapFromFile(imagePath)))
			{
				return E_FAIL;
			}
		}
		else
		{
			bitmap = GetBitmapOrNull(imagePath);
			assert(bitmap != nullptr);
			mAnimationAssetMap.emplace(imagePath, new AnimationAsset(bitmap, frameInfo));
		}
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
}