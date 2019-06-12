#include "WC.h"

/**
 * Writes the list box entries into a text file for later retrieval.
 * PARAMETERS:
 *  wszFileName - A wide string containing the file name to write out to
 *  hListBox - A handle to the list box to write data from
 * RETURNS:
 *  TRUE if successful; FALSE otherwise
 */
_Pre_satisfies_(hListBox != NULL && wszFileName != NULL && wcslen(wszFileName) <= MAX_PATH)
_Success_(return == TRUE)
_Ret_range_(FALSE, TRUE)
_Check_return_
_Must_inspect_result_

BOOL WINAPI WriteFileFromListBox(
	_In_reads_or_z_(MAX_PATH) WCHAR *wszFileName, 
	_In_ HWND hListBox
)
{
	HANDLE hFile;
	CHAR szStr[MAX_PATH];
	CONST CHAR *szLF = "\r\n";
	LONG_PTR lpItems, i;
	DWORD dwWritten, dwLen;
	HRESULT hr;

	hFile = CreateFileW(
		wszFileName,
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

	lpItems = SendMessageW(
		hListBox,
		LB_GETCOUNT,
		0,
		0
	);

	for (i = 0; i < lpItems; i++)
	{
		// Since the values of the list box are loaded with file paths,
		// MAX_PATH is the most sensible limit
		(VOID) SendMessageA(
			hListBox, 
			LB_GETTEXT,
			i,
			(LPARAM)szStr
		);
		
		szStr[MAX_PATH - 1] = '\0';
		
		hr = StringCbLengthA(
			szStr,
			MAX_PATH,
			&dwLen
		);
		
		if (FAILED(hr))
		{
			// One file in the list had a path > MAX_PATH;
			// we caught it; keep trying...
			continue;
		}
		(VOID) WriteFile(
			hFile, 
			szStr,
			dwLen,
			&dwWritten,
			NULL
		);

		(VOID) WriteFile(
			hFile,
			szLF,
			2,
			&dwWritten, 
			NULL
		);
	}

	(VOID) CloseHandle(hFile);

	return TRUE;
}