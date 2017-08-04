#include "WC.h"

/**
 * Callback function for the EnumChildWindows call
 * in wWinMain. Sets all child window fonts to the
 * default GUI font.
 * PARAMETERS:
 *  hWnd - The handle to the child window being processed
 *  lParam - Required by the callback function signature;
 *   unused
 * RETURNS:
 *  TRUE always to indicate to EnumChildWindows to continue
 *   processing child windows.
 */
BOOL CALLBACK EnumChildProc(
	_In_ HWND hWnd, 
	_In_ LPARAM lParam
)
{
	HFONT hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessageW(hWnd, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(TRUE, 0));
	return TRUE;
}