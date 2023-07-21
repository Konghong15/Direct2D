#include "D2DPlatformDemo.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	platform::D2DPlatformDemo platformDemo(1920, 1080, L"platformDemo");
	return gameProcessor::WinApp::Run(&platformDemo, hInstance, nCmdShow);
}
