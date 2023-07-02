#include "WinApp.h"
#include "D2DEntityCamara.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	entityCamara::D2DEntityCamara entityCamara(1920, 1080, L"entityCamara");
	return gameProcessor::WinApp::Run(&entityCamara, hInstance, nCmdShow);
}
