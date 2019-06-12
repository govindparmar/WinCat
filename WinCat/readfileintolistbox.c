#include "WC.h"

/**
 * Reads a file, line by line, into the list box control in the main app window.
 * PARAMETERS:
 *  wszFileName - A wide-string containing the file name to read from
 *  hListBox - A handle to the list box control in the main app window
 * RETURNS:
 *  TRUE if successful; FALSE otherwise
 */

_Pre_satisfies_(hListBox != NULL && wszFileName != NULL && wcslen(wszFileName) <= MAX_PATH)
_Success_(return == TRUE)
_Ret_range_(FALSE, TRUE)
_Check_return_
_Must_inspect_result_

BOOL WINAPI ReadFileIntoListBox(
	_In_reads_or_z_(MAX_PATH) WCHAR *wszFileName, 
	_In_ HWND hListBox
)
{
	CONST HANDLE hHeap = GetProcessHeap();
	HANDLE hFile;
	BYTE *bData = NULL, *pData = NULL;
	LARGE_INTEGER liSize;
	DWORD dwRead, i, dwCount = 0;
	BOOL fRead = FALSE;

	hFile = CreateFileW(
		wszFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return FALSE;
	}

	(VOID) GetFileSizeEx(
		hFile,
		&liSize
	);

	if (
		liSize.HighPart > 0 ||
		liSize.LowPart & 0x80000000
	) 
	{
		// If the high-order 32-bits or the MSB of the 
		// low-order 32-bits are non-zero, the file is 
		// too large.
		SetLastError(ERROR_FILE_TOO_LARGE);
		return FALSE;
	}

	bData = (BYTE *)HeapAlloc(
		hHeap, 
		HEAP_ZERO_MEMORY,
		liSize.LowPart
	);

	if (NULL == bData)
	{
		return FALSE;
	}

	fRead = ReadFile(
		hFile,
		bData,
		liSize.LowPart,
		&dwRead, 
		NULL
	);

	if (FALSE == fRead)
	{
		(VOID) MessageBoxW(
			NULL, 
			L"Unable to read the specified file.", 
			L"Error",
			MB_OK | MB_ICONSTOP
		);

		(VOID) HeapFree(
			hHeap, 
			0,
			bData
		);

		bData = NULL;
		return FALSE;
	}
	(VOID) CloseHandle(hFile);

	pData = bData;

	for (i = 0; i < dwRead; i++)
	{
		if (pData[i] == '\n')
		{
			dwCount++;
		}
	}
	for (i = 0; i < dwRead; i++)
	{
		if (pData[i] == '\n')
		{
			pData[i] = 0;
			
			(VOID) SendMessageA(
				hListBox, 
				LB_ADDSTRING,
				0,
				(LPARAM)pData
			);

			pData += (++i);
			i = 0;
			dwCount--;
			if (0 == dwCount)
			{
				break;
			}
		}
	}
	
	(VOID) HeapFree(
		hHeap,
		0,
		bData
	);

	bData = NULL;
	pData = NULL;
	return TRUE;
}
