#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HWND hEdit, hEdit2;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL isAdmin(HWND hEdit) 
{
	TCHAR expectedText[6] = _T("ADMIN");

	int length = GetWindowTextLength(hEdit);
	if (length != 0)
	{
		TCHAR* buff = new TCHAR[length + 1];
		GetWindowText(hEdit, buff, length + 1);
		bool isAdmin = (_tcscmp(buff, expectedText) == 0);
		delete[] buff;
		return isAdmin;
	}
	else
	{
		return false;
	}
}

BOOL isCorrectPassword(HWND hEdit)
{
	TCHAR password[6] = _T("12345");

	int length = GetWindowTextLength(hEdit);
	if (length != 0)
	{
		TCHAR* buff = new TCHAR[length + 1];
		GetWindowText(hEdit, buff, length + 1);
		bool isPassword = (_tcscmp(buff, password) == 0);
		delete[]buff;
		return isPassword;
	}
	else
	{
		return false;
	}
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:  
		hEdit = GetDlgItem(hWnd, IDC_EDIT1);
		hEdit2 = GetDlgItem(hWnd, IDC_EDIT2);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			if (isAdmin(hEdit)&&isCorrectPassword(hEdit2))
			{
				MessageBox(0, TEXT("Correct!!!"), NULL,MB_OK);
			}
			else if (!isAdmin(hEdit))
			{
				MessageBox(0, TEXT("Something went wrong with Login"), TEXT("Error"), MB_OK);
				SetWindowText(hEdit, _T(""));
			}
			else if (!isCorrectPassword(hEdit2))
			{
				MessageBox(0, TEXT("Something went wrong with the password"), TEXT("Error"), MB_OK);
				SetWindowText(hEdit2, _T(""));
			}
			else
			{
				MessageBox(0, TEXT("Something went wrong..."), TEXT("Error"), MB_OK);
				SetWindowText(hEdit, _T(""));
				SetWindowText(hEdit2, _T(""));

			}
		}
	case WM_SHOWWINDOW:
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}