#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include "time.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HWND hListBox;
HWND hStaticResult;  

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

VOID startBtn(HWND list)
{
	srand(time(NULL));
	int amount = rand() % (20 - 10 + 1) + 10;

	for (int i = 0; i < amount; i++)
	{
		int num = rand() % (10 - (-10) + 1) - 10;

		TCHAR buff[10];
		wsprintf(buff, TEXT("%d"), num);
		SendMessage(list, LB_ADDSTRING, 0, (LPARAM)buff);
	}
}

void sum(HWND list, HWND text)
{
	int amount = SendMessage(list, LB_GETCOUNT, 0, 0);

	int total = 0;
	TCHAR buff[10];

	for (int i = 0; i < amount; i++)
	{
		SendMessage(list, LB_GETTEXT, i, (LPARAM)buff);
		total += _tstoi(buff);
	}

	TCHAR res[20];
	wsprintf(res, TEXT("Sum: %d"), total);
	SetWindowText(text, res);
}

void sub(HWND list, HWND text)
{
	int amount = SendMessage(list, LB_GETCOUNT, 0, 0);
	if (amount == 0) return;

	TCHAR buff[10];
	SendMessage(list, LB_GETTEXT, 0, (LPARAM)buff);
	int total = _tstoi(buff);

	for (int i = 1; i < amount; i++)
	{
		SendMessage(list, LB_GETTEXT, i, (LPARAM)buff);
		total -= _tstoi(buff);
	}

	TCHAR res[20];
	wsprintf(res, TEXT("Subtraction: %d"), total);

	SetWindowText(text, res);
}

void av(HWND list, HWND text)
{
	int amount = SendMessage(list, LB_GETCOUNT, 0, 0);
	if (amount == 0) return;

	int total = 0;
	TCHAR buff[10];

	for (int i = 0; i < amount; i++)
	{
		SendMessage(list, LB_GETTEXT, i, (LPARAM)buff);
		total += _tstoi(buff);
	}

	int average = total / amount;

	TCHAR res[20];
	wsprintf(res, TEXT("Average: %d"), average);

	SetWindowText(text, res);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		hListBox = GetDlgItem(hWnd, IDC_LIST1);
		hStaticResult = GetDlgItem(hWnd, IDC_STATIC);
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			startBtn(hListBox);
		}
			if (IsDlgButtonChecked(hWnd, IDC_RADIO1) == BST_CHECKED)
			{
				sum(hListBox, hStaticResult);
			}
			else if (IsDlgButtonChecked(hWnd, IDC_RADIO2) == BST_CHECKED)
			{
				sub(hListBox, hStaticResult);
			}
			else if (IsDlgButtonChecked(hWnd, IDC_RADIO3) == BST_CHECKED)
			{
				av(hListBox, hStaticResult);  
			}
		
		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
