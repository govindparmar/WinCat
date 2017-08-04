#include "WC.h"


/**
 * Removes all entries presently in the list box.
 * PARAMETERS:
 *  hListBox - The handle to the list box to clear\
 * RETURNS:
 *  TRUE if successful, FALSE otherwise.
 */
_Pre_satisfies_(hListBox != NULL)
_Success_(return == TRUE)
_Ret_range_(FALSE, TRUE)
_Check_return_
_Must_inspect_result_
BOOL WINAPI ClearListBox(
	_In_ HWND hListBox
)
{
	INT i=0, nEntries;
	nEntries = SendMessageW(hListBox, LB_GETCOUNT, 0, 0);
	
	if (nEntries == LB_ERR)
		return FALSE;

	while (i < nEntries)
	{
		// NOTE:  wParam and lParam are both 0 because
		//  once an item is removed from the list, 
		//  the 0-index becomes the next topmost item
		//  in the list box.
		SendMessageW(hListBox, LB_DELETESTRING, 0, 0);
		i++;
	}
	
	return TRUE;
}