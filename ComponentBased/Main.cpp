#include "D2DComponentBased.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	componentBased::D2DComponentBased componentBased(1920, 1080, L"componentBased");
	return gameProcessor::WinApp::Run(&componentBased, hInstance, nCmdShow);
}
