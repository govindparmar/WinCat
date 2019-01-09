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
	BOOL fResult;
	DWORD dwError;
	CONST DWORD dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, dwLang = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
	LPWSTR lpMsgBuf;
	POINTS p0;

	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICSW));
	ncm.cbSize = sizeof(NONCLIENTMETRICSW);

	fResult = SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	if (fResult == FALSE)
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

	hWnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, g_wszClassName, L"WinCat by Govind Parmar", WS_VISIBLE | WS_SYSMENU, 100, 100, 600, 530, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		dwError = GetLastError();
		ReportError(dwError, FALSE);
	}

	ShowWindow(hWnd, SW_SHOW);
	EnumChildWindows(hWnd, EnumChildProc, (LPARAM)&hfDefault);
	UpdateWindow(hWnd);

	while (GetMessageW(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessageW(&Msg);
	}
	
	return (INT) Msg.wParam;
}
