#include "D2DHierarchicalObject.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	hierarchicalObject::D2DHierarchicalObject hierarchicalObject(1920, 1080, L"hierarchicalObject");
	return gameProcessor::WinApp::Run(&hierarchicalObject, hInstance, nCmdShow);
}
