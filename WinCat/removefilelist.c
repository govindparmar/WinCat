#include "WC.h"

/** 
 * Removes the currently highlighted from the list box.
 * PARAMETERS:
 *  hListBox - A handle to the list box in the main app window
 * RETURNS:
 *  TRUE if successful; FALSE otherwise.
 */
_Pre_satisfies_(hListBox != NULL)
_Success_(return == TRUE)
_Ret_range_(FALSE, TRUE)
_Check_return_
_Must_inspect_result_

BOOL WINAPI RemoveFileList(
	_In_ HWND hListBox
)
{
	WPARAM wSel = SendMessageW(hListBox, LB_GETCURSEL, 0, 0);
	if (LB_ERR == wSel) 
	{
		return FALSE;
	}
	else
	{
		(VOID) SendMessageW(hListBox, LB_DELETESTRING, wSel, 0);
	}
	return TRUE;
}