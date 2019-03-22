#include "WC.h"

VOID WINAPI OnPaint(
	_In_ HWND hWnd
)
{
	PAINTSTRUCT ps;

	(VOID) BeginPaint(hWnd, &ps);
	(VOID) EndPaint(hWnd, &ps);

	return;
}