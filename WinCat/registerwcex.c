#include "WC.h"

CONST WCHAR g_wszClassName[] = L"WindowsConcatenatorClass_02";

/**
 * Populates a WNDCLASSEXW structure and registers the window class.
 * PARAMETERS:
 *  hInstance - The HINSTANCE for the app's process
 * RETURNS:
 *  The result of calling RegisterClassExW() on the WNDCLASSEX
 *   structure that was populated. A value of (ATOM)0 indicates
 *   failure.
 */
_Pre_satisfies_(hInstance != NULL)
_Success_(return > 0)
_Ret_range_(0, USHRT_MAX)
_Check_return_
_Must_inspect_result_

ATOM WINAPI RegisterWCEX(
	_In_ _Notnull_ HINSTANCE hInstance
)
{
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEXW));

	if (hInstance == NULL)
	{
		SetLastError(ERROR_BAD_ARGUMENTS);
		return (ATOM)0;
	}

	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wcex.hIcon =
	wcex.hIconSm = LoadIconW(NULL, IDI_APPLICATION);
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WindowProc;
	wcex.lpszClassName = g_wszClassName;
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1);
	
	return RegisterClassExW(&wcex);
}
