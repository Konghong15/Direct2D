#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "D2DFiniteStateMachine.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	int result = 0;
	{
		finiteStateMachine::D2DFiniteStateMachine finiteStateMachine(1920, 1080, L"finiteStateMachine");
		result = gameProcessor::WinApp::Run(&finiteStateMachine, hInstance, nCmdShow);
	}
	_CrtDumpMemoryLeaks();

	return result;
}
