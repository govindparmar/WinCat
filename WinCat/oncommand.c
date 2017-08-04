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
	HWND hLbxEntries = FindWindowExW(hWnd, NULL, L"ListBox", NULL);
	HINSTANCE hInstance = GetModuleHandleW(NULL);
	switch (nID)
	{
	case ID_FILE_NEW:
		ClearListBox(hLbxEntries);
		break;
	case ID_FILE_OPEN:
		OpenFileList(hWnd, hLbxEntries);
		break;
	case ID_FILE_SAVE:
		SaveFileList(hWnd, hLbxEntries);
		break;
	case ID_FILE_EXIT:
		SendMessageW(hWnd, WM_CLOSE, 0, 0);
		break;
	case ID_EDIT_ADDITEM:
		AddFileList(hWnd, hLbxEntries);
		break;
	case ID_EDIT_REMOVEITEM:
		if (RemoveFileList(hLbxEntries) == FALSE)
		{
			MessageBoxW(0, L"Please highlight the item you want removed from the list.", L"WinCat", MB_OK | MB_ICONWARNING);
		}
		break;
	case ID_EDIT_JOINITEMS:
		JoinFileList(hWnd, hLbxEntries);
		break;
	case ID_HELP_ABOUT40006:
		DialogBoxW(hInstance, MAKEINTRESOURCEW(IDD_ABOUT), hWnd, DialogProc);
		break;
	}
}
