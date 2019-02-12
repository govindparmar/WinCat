#include "WC.h"

DECLSPEC_NORETURN
VOID WINAPI ReportError(
	_In_ DWORD dwError,
	_In_range_(FALSE, TRUE) BOOL fRecoverable
)
{
	LPWSTR lpMsgBuf = NULL;

	(VOID) FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, 
		dwError, 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		(LPVOID)&lpMsgBuf, 
		0, 
		NULL
	);

	(VOID) MessageBoxW(
		NULL, 
		lpMsgBuf, 
		L"Error", 
		MB_OK | MB_ICONSTOP
	);

	LocalFree(
		(HLOCAL)lpMsgBuf
	);
	lpMsgBuf = NULL;

	if (fRecoverable == FALSE)
	{
		ExitProcess(
			dwError
		);
	}
}
