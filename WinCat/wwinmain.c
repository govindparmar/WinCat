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
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPWSTR lpCmdLine, 
	_In_ INT nShowCmd
)
{
	HWND hWnd;
	MSG Msg;
	NONCLIENTMETRICSW ncm;
	HFONT hfDefault;
	DWORD dwError;

	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICSW));
	ncm.cbSize = sizeof(NONCLIENTMETRICSW);

	if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0) == FALSE)
	{
		dwError = GetLastError();
		ReportError(dwError, FALSE);
	}

	hfDefault = CreateFontIndirectW(&ncm.lfMessageFont);

	if (RegisterWCEX(hInstance) == (ATOM)0)
	{
		dwError = GetLastError();
		ReportError(dwError, FALSE);
	}

	hWnd = CreateWindowExW(
		WS_EX_OVERLAPPEDWINDOW, g_wszClassName, 
		L"WinCat by Govind Parmar", WS_VISIBLE | WS_SYSMENU, 
		100, 100, 600, 530, 
		NULL, NULL, hInstance, NULL
	);
	if (NULL == hWnd)
	{
		dwError = GetLastError();
		ReportError(dwError, FALSE);
	}

	(VOID) ShowWindow(hWnd, SW_SHOW);
	(VOID) EnumChildWindows(hWnd, EnumChildProc, (LPARAM)&hfDefault);
	(VOID) UpdateWindow(hWnd);

	while (GetMessageW(&Msg, NULL, 0, 0) > 0)
	{
		(VOID) TranslateMessage(&Msg);
		(VOID) DispatchMessageW(&Msg);
	}
	
	return (INT) Msg.wParam;
}
