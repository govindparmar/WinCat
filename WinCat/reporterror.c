#include "WC.h"

_When_(fRecoverable == FALSE, _Analysis_noreturn_)

VOID WINAPI ReportError(
	_In_ DWORD dwError,
	_In_range_(FALSE, TRUE) BOOL fRecoverable
)
{
	LPWSTR lpMsgBuf = NULL;

	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwError, 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPVOID)&lpMsgBuf, 0, NULL);

	MessageBoxW(NULL, lpMsgBuf, L"Error", MB_OK | MB_ICONSTOP);
	
	LocalFree((HLOCAL)lpMsgBuf);
	lpMsgBuf = NULL;

	if (FALSE == fRecoverable)
	{
		ExitProcess(dwError);
	}

	return;
}
