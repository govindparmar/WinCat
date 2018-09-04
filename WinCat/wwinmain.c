#include "WC.h"

/**
 * Entry point for the application.
 * PARAMETERS:
 *  hInstance - A handle to the current instance of the app
 *  hPrevInstance - Unused
 *  lpCmdLine - Unused
 *  nShowCmd - Unused
 * RETURNS:
 *  The return code from the WM_QUIT message, whenever that is posted.
 */
INT APIENTRY wWinMain(
	_In_ HINSTANCE hInstance, 
	_In_ HINSTANCE hPrevInstance, 
	_In_z_ LPWSTR lpCmdLine, 
	_In_ INT nShowCmd
)
{
	HWND hWnd;
	MSG Msg;
	NONCLIENTMETRICSW ncm;
	HFONT hfDefault;

	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICSW));
	ncm.cbSize = sizeof(NONCLIENTMETRICSW);

	SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	hfDefault = CreateFontIndirectW(&ncm.lfMessageFont);

	if (RegisterWCEX(hInstance) == (ATOM)0)
	{
		MessageBoxW(0, L"Window registration failed", L"Error", MB_OK | MB_ICONSTOP);
		return -1;
	}

	hWnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, g_wszClassName, L"WinCat by Govind Parmar", WS_VISIBLE | WS_SYSMENU, 100, 100, 600, 530, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		MessageBoxW(0, L"Window creation failed", L"Error", MB_OK | MB_ICONSTOP);
		return -1;
	}

	ShowWindow(hWnd, SW_SHOW);
	EnumChildWindows(hWnd, EnumChildProc, (LPARAM)&hfDefault);
	UpdateWindow(hWnd);

	while (GetMessageW(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessageW(&Msg);
	}
	
	return Msg.wParam;
}