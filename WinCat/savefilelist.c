#include "WC.h"

/**
 * Saves the currently populated list box into a file.
 * PARAMETERS:
 *  hWnd - A handle to the main app window
 *  hListBox - A handle to the list box
 * RETURNS:
 *  TRUE if successful; FALSE otherwise
 */
_Pre_satisfies_(hWnd != NULL && hListBox != NULL)
_Success_(return == TRUE)
_Ret_range_(FALSE, TRUE)
_Check_return_
_Must_inspect_result_
BOOL WINAPI SaveFileList(
	_In_ HWND hWnd, 
	_In_ HWND hListBox
)
{
	OPENFILENAMEW ofn;
	WCHAR wszFileName[MAX_PATH] = { 0 }, *p;
	
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));
	
	p = wszFileName;

	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = p;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_ENABLEHOOK;
	ofn.lpstrDefExt = L"wcl";
	ofn.lpstrFilter = L"WinCat File Lists (*.wcl)\0*.WCL\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;

	if (GetSaveFileNameW(&ofn))
	{
		return WriteFileFromListBox(wszFileName, hListBox);
	}

	else return FALSE;
}
