#include "WC.h"

VOID WINAPI OnPaint(
	_In_ HWND hWnd
)
{
	PAINTSTRUCT ps;

	if (!BeginPaint(hWnd, &ps))
	{
		ReportError(ERROR_INVALID_HANDLE, TRUE);
	}
	if (!EndPaint(hWnd, &ps))
	{
		ReportError(ERROR_INVALID_HANDLE, TRUE);
	}

	return;
}