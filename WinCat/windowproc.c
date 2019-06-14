#include "WC.h"

/**
 * Message handling procedure for the main app window.
 * PARAMETERS:
 *  hWnd - A handle to the main app window
 *  Msg - The message currently being processed
 *  wParam - Varies by message
 *  lParam - Varies by message
 * RETURNS:
 *  The meaning of the return value varies by message.
 */
LRESULT CALLBACK WindowProc(
	_In_ HWND hWnd, 
	_In_ UINT Msg, 
	_In_ WPARAM wParam, 
	_In_ LPARAM lParam
)
{
	switch (Msg)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
	default:
		return DefWindowProcW(hWnd, Msg, wParam, lParam);
	}
	return 0;
}
