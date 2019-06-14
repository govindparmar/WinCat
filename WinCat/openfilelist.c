#include "WC.h"


/**
 * Opens a previously saved file list to load
 * into the list box.
 * PARAMETERS:
 *  hWnd - A handle to the main app window
 *  hListBox - A handle to the list box control
 * RETURNS:
 *  TRUE if successful; FALSE otherwise
 */
_Pre_satisfies_(hWnd != NULL && hListBox != NULL)
_Success_(return == TRUE)
_Ret_range_(FALSE, TRUE)
_Check_return_
_Must_inspect_result_

BOOL WINAPI OpenFileList(
	_In_ HWND hWnd, 
	_In_ HWND hListBox
)
{
	OPENFILENAMEW ofn;
	WCHAR lpFileName[MAX_PATH], *p;

	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));
	ZeroMemory(lpFileName, MAX_PATH * sizeof(WCHAR));

	p = &lpFileName[0];

	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = p;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = L"WinCat File Lists (*.wcl)\0*.WCL\0All Files (*.*)\0*.*\0\0";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_ENABLEHOOK | OFN_HIDEREADONLY;
	ofn.nFilterIndex = 1;

	if (GetOpenFileNameW(&ofn))
	{
		return ReadFileIntoListBox(lpFileName, hListBox);
	}

	else
	{
		return FALSE;
	}
}
