#include "D2DEntityComponentSystem.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	entityComponentSystem::D2DEntityComponentSystem entityComponentSystem(1920, 1080, L"entityComponentSystem");
	return gameProcessor::WinApp::Run(&entityComponentSystem, hInstance, nCmdShow);
}
