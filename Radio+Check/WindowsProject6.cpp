#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
TCHAR grade[50];

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			int counter = 0;
			if (IsDlgButtonChecked(hWnd, IDC_RADIO2) == BST_CHECKED)
			{
				counter += 20;
			}
			 if (IsDlgButtonChecked(hWnd, IDC_RADIO6) == BST_CHECKED)
			{
				counter += 20;
			}
			 if (IsDlgButtonChecked(hWnd, IDC_RADIO7) == BST_CHECKED)
			{
				counter += 20;
			}
			 if (IsDlgButtonChecked(hWnd, IDC_CHECK1) == BST_CHECKED)
			{
				counter += 10;
			}
			 if (IsDlgButtonChecked(hWnd, IDC_CHECK2) == BST_CHECKED)
			{
				counter += 10;
			}
			 if (IsDlgButtonChecked(hWnd, IDC_CHECK4) == BST_CHECKED)
			{
				counter += 10;
			}
			 if (IsDlgButtonChecked(hWnd, IDC_CHECK5) == BST_CHECKED)
			{
				counter += 10;
			}

			wsprintf(grade, TEXT("Your score is: %d"), counter);
			MessageBox(hWnd, grade, TEXT("Result"), MB_OK);
		}

		return TRUE;
	case WM_SHOWWINDOW:
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
