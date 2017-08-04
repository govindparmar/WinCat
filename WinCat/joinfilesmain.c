#include "WC.h"

/**
 * Inner function for joining files together.
 * Goes through each of the files in the list box,
 * reads them 100000 bytes at a time (max) and writes
 * them out to a new file.
 * PARAMETERS:
 *  hListBox - A handle to the listbox containing file names
 *  wszOutFile - A wide string containing the destination output
 *   file
 * RETURNS:
 *  TRUE if successful; FALSE otherwise.
 */
_Pre_satisfies_(hListBox != NULL && wszOutFile != NULL && wcslen(wszOutFile) <= MAX_PATH)
_Success_(return == TRUE)
_Ret_range_(FALSE, TRUE)
_Check_return_
_Must_inspect_result_
BOOL WINAPI JoinFilesMain(
	_In_ HWND hListBox, 
	_In_reads_or_z_(MAX_PATH) WCHAR *wszOutFile
)
{
	HANDLE hFile, hIN;
	BYTE bData[100000];
	DWORD dwRead, dwWritten;
	LONG_PTR lpResult = 0;
	WPARAM i = 0;
	WCHAR wszInFile[MAX_PATH];

	hFile = CreateFileW(wszOutFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	while (1)
	{
		lpResult = SendMessageW(hListBox, LB_GETTEXT, i++, (LPARAM)wszInFile);
		if (lpResult == LB_ERR) break;
		hIN = CreateFileW(wszInFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hIN == INVALID_HANDLE_VALUE)
		{
			WCHAR wMsg[512];
			StringCchPrintfW(wMsg, 512, L"Unable to open the file: %s.\n", wszInFile);
			MessageBoxW(0, wMsg, L"WinCat", MB_OK | MB_ICONWARNING);
			return FALSE;
		}
		do
		{
			SetFilePointer(hFile, 0, NULL, FILE_END);
			ReadFile(hIN, bData, 100000, &dwRead, NULL);
			WriteFile(hFile, bData, dwRead, &dwWritten, NULL);
		}
		while (dwRead != 0);
		CloseHandle(hIN);
	}
	CloseHandle(hFile);
	return TRUE;
}