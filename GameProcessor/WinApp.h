#pragma once

#include <Windows.h>

namespace gameProcessor
{
	class GameProcessor;

	class WinApp
	{
	public:
		static int Run(GameProcessor* pSample, HINSTANCE hInstance, int nCmdShow);
		static HWND GetHwnd();

	protected:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		static void placeInCenterOfScreen(HWND window, DWORD style, DWORD exStyle);

	private:
		static HWND mHwnd;
	};
}