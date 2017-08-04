// WinCat: concatenate multiple files together
// Developed by Govind Parmar
#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <strsafe.h>
#include <sal.h>
#include "resource.h"

#define EXTERN extern

#pragma comment(lib, "comctl32.lib")

#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

EXTERN CONST WCHAR g_wszClassName[];

BOOL WINAPI AddFileList(_In_ HWND hWnd, _In_ HWND hListBox);
BOOL WINAPI ClearListBox(_In_ HWND hListBox);
INT_PTR CALLBACK DialogProc(_In_ HWND hDlg, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
BOOL CALLBACK EnumChildProc(_In_ HWND hWnd, _In_ LPARAM lParam);
BOOL WINAPI JoinFileList(_In_ HWND hWnd, _In_ HWND hListBox);
BOOL WINAPI JoinFilesMain(_In_ HWND hListBox, _In_reads_or_z_(MAX_PATH) WCHAR *wszOutFile);
VOID WINAPI OnClose(_In_ HWND hWnd);
VOID WINAPI OnCommand(_In_ HWND hWnd, _In_ INT nID, _In_ HWND hwSource, _In_ UINT uNotify);
BOOL WINAPI OnCreate(_In_ HWND hWnd, _In_ LPCREATESTRUCTW lpCreateStruct);
VOID WINAPI OnDestroy(_In_ HWND hWnd);
BOOL WINAPI OpenFileList(_In_ HWND hWnd, _In_ HWND hListBox);
BOOL WINAPI ReadFileIntoListBox(_In_reads_or_z_(MAX_PATH) WCHAR *wszFileName, _In_ HWND hListBox);
ATOM WINAPI RegisterWCEX(_In_ HINSTANCE hInstance);
BOOL WINAPI RemoveFileList(_In_ HWND hListBox);
BOOL WINAPI SaveFileList(_In_ HWND hWnd, _In_ HWND hListBox);
LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
BOOL WINAPI WriteFileFromListBox(_In_reads_or_z_(MAX_PATH) WCHAR *wszFileName, _In_ HWND hListBox);
INT APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_z_ LPWSTR lpCmdLine, _In_ INT nShowCmd);
