#include "WC.h"

CONST SIZE_T cbCopyTime = 100000;

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
	HANDLE hFile, hIN, hHeap = GetProcessHeap();
	BYTE *bData = NULL;
	DWORD dwRead, dwWritten;
	LONG_PTR lpResult = 0;
	WPARAM i = 0;
	WCHAR wszInFile[MAX_PATH];
	BOOL fRead = FALSE;

	ZeroMemory(wszInFile, MAX_PATH * sizeof(WCHAR));

	hFile = CreateFileW(
		wszOutFile, 
		GENERIC_READ | GENERIC_WRITE, 
		0, 
		NULL, 
		CREATE_NEW, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL
	);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return FALSE;
	}

	bData = (BYTE *)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, cbCopyTime);
	if (NULL == bData)
	{
		(VOID) MessageBoxW(NULL, L"Out of memory", L"Error", MB_OK | MB_ICONSTOP);
		ExitProcess(ERROR_OUTOFMEMORY);
	}

	while (TRUE)
	{
		lpResult = SendMessageW(hListBox, LB_GETTEXT, i++, (LPARAM)wszInFile);
		wszInFile[259] = L'\0';

		if (LB_ERR == lpResult)
		{
			break;
		}
		
		hIN = CreateFileW(
			wszInFile,
			GENERIC_READ, 
			0, 
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		
		if (hIN == INVALID_HANDLE_VALUE)
		{
			WCHAR wMsg[512];
			(VOID) StringCchPrintfW(wMsg, 512, L"Unable to open the file: %s.\n", wszInFile);
			(VOID) MessageBoxW(0, wMsg, L"WinCat", MB_OK | MB_ICONWARNING);
			return FALSE;
		}
		
		do
		{
			(VOID) SetFilePointer(hFile, 0, NULL, FILE_END);
			fRead = ReadFile(hIN, bData, cbCopyTime, &dwRead, NULL);
			if (fRead)
			{
				(VOID) WriteFile(hFile, bData, dwRead, &dwWritten, NULL);
			}
		}
		while (dwRead != 0);
		
		(VOID) CloseHandle(hIN);
	}

	(VOID) CloseHandle(hFile);
	(VOID) HeapFree(hHeap, 0, bData);

	bData = NULL;
	
	return TRUE;
}