#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <fstream>
using namespace std;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HWND hEdit;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}


DWORD WINAPI THREADtext(LPVOID lp)
{
	int length = GetWindowTextLength(hEdit);
	TCHAR* buff = new TCHAR[length + 1];
	GetWindowText(hEdit, buff, length + 1);

	wofstream file(TEXT("Text.txt"));
	if (file.is_open())
	{
		file << buff;
		file.close();
		MessageBox(NULL, TEXT("Text File has been created"), NULL, 0);
	}
	return 0;
}

DWORD WINAPI THREADbinary(LPVOID lp)
{
	int length = GetWindowTextLength(hEdit);
	TCHAR* buff = new TCHAR[length + 1];
	GetWindowText(hEdit, buff, length + 1);
	ofstream file(TEXT("binary.txt"), ios::binary);
	file << buff;
	file.close();
	Sleep(500);
	MessageBox(NULL, TEXT("Binary File has been created"), NULL, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		hEdit = GetDlgItem(hWnd, IDC_EDIT1);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			if (IsDlgButtonChecked(hWnd, IDC_CHECK2) == BST_CHECKED)
			{
				CreateThread(NULL, 0, THREADbinary, NULL, 0, NULL);
			}
			if (IsDlgButtonChecked(hWnd, IDC_CHECK1) == BST_CHECKED)
			{
				CreateThread(NULL, 0, THREADtext, NULL, 0, NULL);
			}
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