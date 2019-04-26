#include "WC.h"

/**
 * Message cracker for WM_DESTROY.
 * Posts WM_QUIT to the main app window.
 * PARAMETERS:
 *  hWnd - A handle to the main app window
 */
VOID WINAPI OnDestroy(
	_In_ HWND hWnd
)
{
	UNREFERENCED_PARAMETER(hWnd);
	PostQuitMessage(0);
}
