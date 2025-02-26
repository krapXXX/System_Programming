#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <fstream>
using namespace std;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

DWORD WINAPI THREAD1(LPVOID lp)
{
    ofstream file("File1.txt");
    if (file.is_open())
    {
        file << "Hello world";
        file.close();
        MessageBox(NULL, TEXT("File1 has been created"), NULL, 0);
    }
    return 0;
}

DWORD WINAPI THREAD2(LPVOID lp)
{
    ofstream file("File2.txt");
    if (file.is_open())
    {
        file << "12345";
        file.close();
        MessageBox(NULL, TEXT("File2 has been created"), NULL, 0);
    }
    return 0;
}

DWORD WINAPI THREAD3(LPVOID lp)
{
    ofstream file("File3.txt");
    if (file.is_open())
    {
        file << "Arina";
        file.close();
        MessageBox(NULL, TEXT("File3 has been created"), NULL, 0);
    }
    return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        if (wParam == IDC_BUTTON1)
        {
            EndDialog(hWnd, 0);
            return TRUE;
        }
        return TRUE;
    case WM_LBUTTONDOWN: 
    {
        HWND hStatic = GetDlgItem(hWnd, IDC_STATIC);
        RECT rect;
        GetWindowRect(hStatic, &rect);

        POINT pt;
        GetCursorPos(&pt);

        if (PtInRect(&rect, pt)) 
        {
            CreateThread(NULL, 0, THREAD1, NULL, 0, NULL);
            CreateThread(NULL, 0, THREAD2, NULL, 0, NULL);
            CreateThread(NULL, 0, THREAD3, NULL, 0, NULL);
        }
        return TRUE;
    }
    case WM_SHOWWINDOW:
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}