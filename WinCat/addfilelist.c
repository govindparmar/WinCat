#include "WC.h"

/**
 * Adds a new item into the file list box.
 * PARAMETERS:
 *  hWnd - The handle to the main app window
 *  hListBox - The handle to the listbox in the main app window
 * RETURNS:
 *  TRUE if the user selected a valid file, FALSE otherwise.
 */
_Pre_satisfies_(hWnd != NULL && hListBox != NULL)
_Success_(return == TRUE)
_Ret_range_(FALSE, TRUE)
_Check_return_
_Must_inspect_result_

BOOL WINAPI AddFileList(
	_In_ HWND hWnd, 
	_In_ HWND hListBox
)
{
	OPENFILENAMEW ofn;
	WCHAR wszFileName[MAX_PATH], *p;

	ZeroMemory(
		&ofn,
		sizeof(OPENFILENAMEW)
	);
	ZeroMemory(
		wszFileName,
		MAX_PATH * sizeof(WCHAR)
	);

	p = &wszFileName[0];

	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.lpstrFile = p;
	ofn.hwndOwner = hWnd;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = L"All Files (*.*)\0*.*\0\0";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_ENABLEHOOK | OFN_HIDEREADONLY;
	ofn.nFilterIndex = 1;

	if (GetOpenFileNameW(&ofn))
	{
		(VOID) SendMessageW(
			hListBox, 
			LB_ADDSTRING, 
			0,
			(LPARAM)wszFileName
		);

		return TRUE;
	}

	else
	{
		return FALSE;
	}
}
