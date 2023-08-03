#include "D2DRigidbodyAABB.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	d2dRigidbodyAABB::D2DRigidbodyAABB demo(1920, 1080, L"demo");
	return d2dFramework::WinApp::Run(&demo, hInstance, nCmdShow);
}
