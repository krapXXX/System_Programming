#include <windows.h>
#include <tchar.h>
#include "resource.h"

HWND hStart, hStop, hPicture;
HBITMAP hBmp[5];

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc); 
}

VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	static int index = 0;
	index++;
	if (index > 4)
		index = 0;
	SendMessage(hPicture, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[index]));
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return TRUE;

		case WM_INITDIALOG:
			hStart = GetDlgItem(hWnd, IDC_START);
			hStop = GetDlgItem(hWnd, IDC_STOP);
			hPicture = GetDlgItem(hWnd, IDC_PICTURE);
			for(int i = 0; i < 5; i++)
				hBmp[i] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1 + i));
			return TRUE;

		case WM_COMMAND:
			if(LOWORD(wParam) == IDC_START)
			{
				SetTimer(hWnd, 1, 1000, TimerProc);
				EnableWindow(hStart, FALSE);
				EnableWindow(hStop, TRUE);
				SetFocus(hStop);
			}
			else if(LOWORD(wParam) == IDC_STOP)
			{
				KillTimer(hWnd, 1);
				EnableWindow(hStart, TRUE);
				EnableWindow(hStop, FALSE);
				SetFocus(hStart);
			}
			return TRUE;
	}
	return FALSE;
}