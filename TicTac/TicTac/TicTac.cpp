#include <windows.h>
#include <tchar.h>
#include "resource.h"

HBITMAP hBtnX, hBtnO;
HWND hButtons[9];
int clickCounter = 1;
int board[9] = { 0 };
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CheckWinner()
{
	int victory[8][3] =
	{ {0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{0, 3, 6},
		{1, 4, 7},
		{2, 5, 8},
		{0, 4, 8},
		{2, 4, 6} };
	for (int i = 0; i < 8; i++)
	{
		int *btn = victory[i];
		if (board[btn[0]] != 0 && board[btn[0]] == board[btn[1]] && board[btn[1]] == board[btn[2]])
		{
			return true;
		}
	}
	return false;
}
void OnBtnClick(HWND hButton, int btnIndex)
{
	HBITMAP hBtnImg;
	int player;
	if (clickCounter % 2 == 1)
	{
		player = 1;
		hBtnImg = hBtnX;
	}
	else
	{
		player = 2;
		hBtnImg = hBtnO;
	}
	SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBtnImg);
	board[btnIndex] = player;
	SetWindowPos(hButton, NULL, 0, 0, 50, 50, SWP_NOMOVE);
	EnableWindow(hButton, FALSE);
	if (CheckWinner())
	{
		if (player == 1)
		{
			MessageBox(hButton, TEXT("Cross wins!"), _T("Game Over"), MB_OK);
			return;
		}
		else
		{
			MessageBox(hButton, TEXT("Circle wins!"), _T("Game Over"), MB_OK);
			return;
		}
	}
if(clickCounter ==9)
	{
		MessageBox(hButton, TEXT("Friendship wins!"), _T("Game Over"), MB_OK);
	}
	clickCounter++;
	
}


INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		hBtnX = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
		hBtnO = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));

		for (int i = 0; i < 9; i++)
		{
			hButtons[i] = GetDlgItem(hWnd, IDC_BUTTON1 + i);
			SetWindowLong(hButtons[i], GWL_STYLE, GetWindowLong(hButtons[i], GWL_STYLE) | BS_BITMAP);
		}

		return TRUE;

	case WM_COMMAND:
		for (int i = 0; i < 9; i++)
		{
			if (LOWORD(wParam) == (IDC_BUTTON1 + i))
			{
				OnBtnClick(hButtons[i], i);
			}
		}
		return TRUE;
	case WM_CLOSE:
		DeleteObject(hBtnX);
		DeleteObject(hBtnO);
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}