#include "WC.h"

/**
 * Message cracker for WM_CREATE.
 * Initializes the common controls library, and creates
 * the child windows for the main app window.
 * PARAMETERS:
 *  hWnd - A handle to the main app window
 *  lpCreateStruct - A structure containing information
 *   about the window being created
 * RETURNS:
 *  TRUE if successful; FALSE otherwise
 */
_Success_(return == TRUE)
BOOL WINAPI OnCreate(
	_In_ HWND hWnd, 
	_In_ LPCREATESTRUCTW lpCreateStruct
)
{
	INITCOMMONCONTROLSEX iccx;
	HINSTANCE hInstance = lpCreateStruct->hInstance;
	HWND hLbxEntries;
	
	iccx.dwICC = ICC_STANDARD_CLASSES;
	iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	
	if (!InitCommonControlsEx(&iccx)) 
	{
		return FALSE;
	}
	
	hLbxEntries = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, L"ListBox", L"", 
		WS_VISIBLE | WS_CHILD | WS_VSCROLL | LBS_DISABLENOSCROLL, 
		10, 10, 560, 460, 
		hWnd, NULL, hInstance, NULL);
	
	return (hLbxEntries != INVALID_HANDLE_VALUE);
}
