#include "WC.h"

/**
 * Message cracker for WM_COMMAND.
 * Handles menu item events.
 * PARAMETERS:
 *  hWnd - A handle to the main app window
 *  nID - The ID for dialog box/menu events
 *  hwSource - A handle to the child window
 *   that is the source of WM_COMMAND, if
 *   applicable
 *  uNotify - The control notification code
 */
VOID WINAPI OnCommand(
	_In_ HWND hWnd, 
	_In_ INT nID, 
	_In_ HWND hwSource, 
	_In_ UINT uNotify
)
{
	CONST HINSTANCE hInstance = GetModuleHandleW(NULL);
	HWND hLbxEntries = FindWindowExW(hWnd, NULL, L"ListBox", NULL);

	switch (nID)
	{
	case ID_FILE_NEW:
		if (FALSE == ClearListBox(hLbxEntries))
		{
			MessageBoxW(NULL, L"Unable to clear the list box.", L"Error", MB_OK | MB_ICONSTOP);
		}
		break;
	case ID_FILE_OPEN:
		if (FALSE == OpenFileList(hWnd, hLbxEntries))
		{
			MessageBoxW(NULL, L"Could not open the specified file.", L"Error", MB_OK | MB_ICONSTOP);
		}
		break;
	case ID_FILE_SAVE:
		if (FALSE == SaveFileList(hWnd, hLbxEntries))
		{
			MessageBoxW(NULL, L"Unable to save the current list.", L"Error", MB_OK | MB_ICONSTOP);
		}
		break;
	case ID_FILE_EXIT:
		SendMessageW(hWnd, WM_CLOSE, 0, 0);
		break;
	case ID_EDIT_ADDITEM:
		if (FALSE == AddFileList(hWnd, hLbxEntries))
		{
			MessageBoxW(NULL, L"Could not add that item to the list.", L"Error", MB_OK | MB_ICONSTOP);
		}
		break;
	case ID_EDIT_REMOVEITEM:
		if (FALSE == RemoveFileList(hLbxEntries))
		{
			MessageBoxW(NULL, L"Please highlight the item you want removed from the list.", L"WinCat", MB_OK | MB_ICONWARNING);
		}
		break;
	case ID_EDIT_JOINITEMS:
		if (FALSE == JoinFileList(hWnd, hLbxEntries))
		{
			MessageBoxW(NULL, L"Could not join the files together.", L"Error", MB_OK | MB_ICONSTOP);
		}
		break;
	case ID_HELP_ABOUT40006:
		DialogBoxW(hInstance, MAKEINTRESOURCEW(IDD_ABOUT), hWnd, DialogProc);
		break;
	}
}
