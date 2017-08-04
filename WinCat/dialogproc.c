#include "WC.h"

/**
 * Handler procedure for the "About" dialog.
 * PARAMETERS:
 *  hDlg - Handle to the dialog
 *  Msg - The message being processed
 *  wParam - Varies by message
 *  lParam - Varies by message
 * RETURNS:
 *  TRUE if a message was explicitly handled by this function,
 *  FALSE otherwise.
 */
INT_PTR CALLBACK DialogProc(
	_In_ HWND hDlg, 
	_In_ UINT Msg, 
	_In_ WPARAM wParam, 
	_In_ LPARAM lParam
)
{
	switch (Msg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		EndDialog(hDlg, (INT_PTR)0);
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDB_OK)
			EndDialog(hDlg, (INT_PTR)0);
	}
	return (INT_PTR)FALSE;
}