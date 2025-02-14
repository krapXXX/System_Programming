#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HWND hStatic;
HINSTANCE hInst;
HCURSOR cursor1, cursor2, cursor3;


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		MoveWindow(hWnd, 50, 50, 750, 500, TRUE);
		cursor1 = LoadCursor(NULL, MAKEINTRESOURCE(IDC_CURSOR1));
		cursor2 = LoadCursor(NULL, MAKEINTRESOURCE(IDC_NODROP));
		cursor3 = LoadCursor(NULL, MAKEINTRESOURCE(IDC_POINTER));

		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	case WM_MOUSEMOVE:
		int x = LOWORD(lParam);
		if (x <= 150)
		{
			SetCursor(cursor1);
		}
		else if (x > 150 && x < 600)
		{
			SetCursor(cursor2);
		}
		else
		{
			SetCursor(cursor3);
		}
	}
	return FALSE; 
}

