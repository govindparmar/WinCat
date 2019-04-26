#include "WC.h"

/**
 * Joins all the files that are presently named in the list box
 * into a single continuous file.
 * PARAMETERS:
 *  hWnd - A handle to the main app window
 *  hListBox - A handle to the listbox containing the file names to join
 * RETURNS:
 *  TRUE if successful; FALSE otherwise.
 */
_Pre_satisfies_(hWnd != NULL && hListBox != NULL)
_Success_(return == TRUE)
_Ret_range_(FALSE, TRUE)
_Check_return_
_Must_inspect_result_

BOOL WINAPI JoinFileList(
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
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = p;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_ENABLEHOOK;
	ofn.lpstrFilter = L"All Files (*.*)\0*.*\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;

	if (GetSaveFileNameW(&ofn))
	{
		if (
			!JoinFilesMain(
				hListBox,
				wszFileName
			)
		)
		{
			(VOID) MessageBoxW(
				NULL, 
				L"At least one file could not be joined.", 
				L"Warning", 
				MB_OK | MB_ICONWARNING
			);
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
