#include "WC.h"

VOID WINAPI OnPaint(
	_In_ HWND hWnd
)
{
	PAINTSTRUCT ps;
	BeginPaint(hWnd, &ps);
	EndPaint(hWnd, &ps);

	return;
}