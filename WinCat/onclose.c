#include "WC.h"

/**
 * Message cracker for WM_CLOSE.
 * Posts WM_DESTROY to the window.
 * PARAMETERS:
 *  hWnd - The window being closed
 */
VOID WINAPI OnClose(
	_In_ HWND hWnd
)
{
	(VOID) DestroyWindow(
		hWnd
	);
}
