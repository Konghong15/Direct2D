#include "D2DTransform.h"
#include "WinApp.h"
#include "Object.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	gameProcessor::Object::mObject.push_back(nullptr);
	project2::D2DTransform transform(1920, 1080, L"First");
	return gameProcessor::WinApp::Run(&transform, hInstance, nCmdShow);
}
