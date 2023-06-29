#include "D2DCamara.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	camara::D2DCamara camara(1920, 1080, L"camara");
	return gameProcessor::WinApp::Run(&camara, hInstance, nCmdShow);
}
