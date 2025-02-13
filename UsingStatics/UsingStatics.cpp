#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
int counter = 1, WIDTH, HEIGHT, minWIDTH = 30, minHEIGHT = 30, MAINLEFT, MAINTOP, LEFT1, LEFT2, TOP1, TOP2;
HWND hStatic;
HINSTANCE hInst;
bool isDrawing = false;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_LBUTTONDOWN:
		LEFT1 = LOWORD(lParam);
		TOP1 = HIWORD(lParam);
		isDrawing = true;
		return TRUE;

	case WM_LBUTTONUP:
		if (isDrawing)
		{
			LEFT2 = LOWORD(lParam);
			TOP2 = HIWORD(lParam);
			isDrawing = false;

			WIDTH = abs(LEFT2 - LEFT1);
			HEIGHT = abs(TOP2 - TOP1);
			MAINLEFT = min(LEFT1, LEFT2);
			MAINTOP = min(TOP1, TOP2);

			if (WIDTH <= minWIDTH && HEIGHT <= minHEIGHT)
			{
				MessageBox(hWnd, _T("The box is too little"), _T("RULE"), MB_OK | MB_ICONWARNING);
				return true;
			}

			TCHAR counterText[10];
			_stprintf_s(counterText, _T("%d"), counter);

			hStatic = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), counterText,
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER,
				MAINLEFT, MAINTOP, WIDTH, HEIGHT, hWnd, NULL, hInst, NULL);
			counter++;
		}
		return TRUE;
	}
	return FALSE;
}
