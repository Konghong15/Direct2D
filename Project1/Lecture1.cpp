// Lecture1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Lecture1.h"

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <d2d1helper.h>

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "windowscodecs")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND g_hwnd;
ID2D1Factory* g_pFactory;
ID2D1HwndRenderTarget* g_pRenderTarget;
ID2D1SolidColorBrush* g_pBlackBrush;
ID2D1SolidColorBrush* g_pRedBrush;
D2D1_RECT_F g_player_rect;
D2D1_ELLIPSE ellipse;
IDWriteFactory* g_pDWriteFactory;
IDWriteTextFormat* g_pWriteTextFormat;
IWICImagingFactory* g_pWICFactory;
ID2D1Bitmap* g_pBitmap;

bool InitD2D(void)
{
	RECT rc;
	GetClientRect(g_hwnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(
		static_cast<UINT>(rc.right - rc.left),
		static_cast<UINT>(rc.bottom - rc.top)
	);

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pFactory);
	if (FAILED(hr))
	{
		return false;
	}

	hr = g_pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(g_hwnd, size),
		&g_pRenderTarget);
	if (FAILED(hr))
	{
		return false;
	}

	hr = g_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black),
		&g_pBlackBrush
	);
	if (FAILED(hr))
	{
		return false;
	}

	hr = g_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red),
		&g_pRedBrush
	);
	if (FAILED(hr))
	{
		return false;
	}

	// Create a DirectWrite factory.
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(g_pDWriteFactory),
		reinterpret_cast<IUnknown**>(&g_pDWriteFactory)
	);
	if (FAILED(hr))
	{
		return false;
	}

	hr = g_pDWriteFactory->CreateTextFormat(
		L"Gabriola",
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		60.0f,
		L"en-us",
		&g_pWriteTextFormat
	);
	if (FAILED(hr))
	{
		return false;
	}
	g_pWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	g_pWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		reinterpret_cast<void**>(&g_pWICFactory)
	);
	if (FAILED(hr))
	{
		return false;
	}

	//{
	//	HRSRC imageResHandle = FindResourceW(NULL, L"Jump.png", L"Image");
	//	hr = (imageResHandle ? S_OK : E_FAIL);
	//	if (FAILED(hr))
	//	{
	//		return false;
	//	}

	//	HGLOBAL imageResDataHandle = LoadResource(NULL, imageResHandle);
	//	hr = (imageResDataHandle ? S_OK : E_FAIL);
	//	if (FAILED(hr))
	//	{
	//		return false;
	//	}

	//	void* pImageFile = LockResource(imageResDataHandle);
	//	hr = (pImageFile ? S_OK : E_FAIL);
	//	if (FAILED(hr))
	//	{
	//		return false;
	//	}

	//	DWORD imageFileSize = SizeofResource(NULL, imageResHandle);
	//	hr = (pImageFile ? S_OK : E_FAIL);
	//	if (FAILED(hr))
	//	{
	//		return false;
	//	}

	//	IWICStream* pIWICStream = NULL;
	//	hr = g_pWICFactory->CreateStream(&pIWICStream);
	//	if (FAILED(hr))
	//	{
	//		return false;
	//	}

	//	hr = pIWICStream->InitializeFromMemory(
	//		reinterpret_cast<BYTE*>(pImageFile),
	//		imageFileSize);
	//	if (FAILED(hr))
	//	{
	//		return false;
	//	}

	//	IWICBitmapDecoder* pIDecoder;
	//	hr = g_pWICFactory->CreateDecoderFromStream(
	//		pIWICStream,                   // The stream to use to create the decoder
	//		NULL,                          // Do not prefer a particular vendor
	//		WICDecodeMetadataCacheOnLoad,  // Cache metadata when needed
	//		&pIDecoder);

	//	IWICBitmapFrameDecode* pIDecoderFrame = NULL;
	//	hr = pIDecoder->GetFrame(0, &pIDecoderFrame);

	//	IWICFormatConverter* pConverter = NULL;
	//	IWICBitmapFrameDecode* pSource = NULL;
	//	hr = g_pWICFactory->CreateFormatConverter(&pConverter);
	//	hr = pConverter->Initialize(
	//		pSource,
	//		GUID_WICPixelFormat32bppPBGRA,
	//		WICBitmapDitherTypeNone,
	//		NULL,
	//		0.f,
	//		WICBitmapPaletteTypeMedianCut
	//	);

	//	hr = g_pRenderTarget->CreateBitmapFromWicBitmap(
	//		pConverter,
	//		NULL,
	//		&g_pBitmap
	//	);
	//}

	ellipse = D2D1::Ellipse(D2D1::Point2F(100, 100), 100, 100);

	g_player_rect = { 100, 100, 200,200 };



	return true;
}

void ReleaseD2D(void)
{
	g_pFactory->Release();
	g_pRenderTarget->Release();
	g_pBlackBrush->Release();
	g_pRedBrush->Release();
	g_pDWriteFactory->Release();
	g_pWriteTextFormat->Release();
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LECTURE1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LECTURE1));

	if (!InitD2D())
	{
		return 0;
	}

	MSG msg = { 0, };

	bool bLeft = false;

	// 기본 메시지 루프입니다:
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			continue;
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			g_player_rect.right -= 1;
			g_player_rect.left -= 1;
			// InvalidateRect(g_hwnd, nullptr, false);
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			g_player_rect.right += 1;
			g_player_rect.left += 1;
			// InvalidateRect(g_hwnd, nullptr, false);
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			g_player_rect.top -= 1;
			g_player_rect.bottom -= 1;
			// InvalidateRect(g_hwnd, nullptr, false);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			g_player_rect.top += 1;
			g_player_rect.bottom += 1;
			// InvalidateRect(g_hwnd, nullptr, false);
		}

		if (!bLeft)
		{
			ellipse.point.x += 5;
		}
		else
		{
			ellipse.point.x -= 5;
		}

		if (ellipse.point.x < 0)
		{
			bLeft = false;
		}
		else if (ellipse.point.x > 1000)
		{
			bLeft = true;
		}

		g_pRenderTarget->BeginDraw();
		{
			D2D1::ColorF color(D2D1::ColorF::Red);

			g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

			WCHAR text[32] = L"야미";
			g_pRenderTarget->DrawText(
				text,
				lstrlenW(text),
				g_pWriteTextFormat,
				D2D1::RectF(1020, 0, 1200, 200),
				g_pBlackBrush
			);
			g_pRenderTarget->FillRectangle(g_player_rect, g_pBlackBrush);
			g_pRenderTarget->FillEllipse(ellipse, g_pRedBrush);
			// g_pRenderTarget->DrawBitmap(g_pBitmap, D2D1::RectF(0.0f, 0.0f, 32, 30));
		}
		g_pRenderTarget->EndDraw();
	}

	ReleaseD2D();

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LECTURE1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LECTURE1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	g_hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!g_hwnd)
	{
		return FALSE;
	}

	ShowWindow(g_hwnd, nCmdShow);
	UpdateWindow(g_hwnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
