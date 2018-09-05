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
	HANDLE hFile = CreateFileW(wszFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL), hHeap = GetProcessHeap();
	BYTE *bData = NULL, *pData = NULL;
	LARGE_INTEGER liSize;
	DWORD dwRead, i, dwCount = 0;
	BOOL fRead = FALSE;

	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	GetFileSizeEx(hFile, &liSize);

	if (liSize.HighPart > 0 || liSize.LowPart & 0x80000000) // too big
		return FALSE;

	bData = (BYTE *)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, liSize.LowPart);
	if (bData == NULL) 
		return FALSE;

	fRead = ReadFile(hFile, bData, liSize.LowPart, &dwRead, NULL);
	if (!fRead)
	{
		MessageBoxW(NULL, L"Unable to read the specified file.", L"Error", MB_OK | MB_ICONSTOP);
		HeapFree(hHeap, 0, bData);
		bData = NULL;
		return FALSE;
	}
	CloseHandle(hFile);

	pData = bData;

	for (i = 0; i < dwRead; i++)
		if (pData[i] == '\n')
			dwCount++;
	
	for(i = 0; i < dwRead; i++)
		if(pData[i]=='\n')
		{
			pData[i] = 0;
			SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)pData);
			pData += (++i);
			i = 0;
			dwCount--;
			if(dwCount == 0) break;
		}
	
			
	
	HeapFree(hHeap, 0, bData);
	bData = NULL;
	pData = NULL;
	return TRUE;
}
