#include "D2DFirst.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	project1::D2DFirst first(1920, 1080, L"First");
	return gameProcessor::WinApp::Run(&first, hInstance, nCmdShow);
}
