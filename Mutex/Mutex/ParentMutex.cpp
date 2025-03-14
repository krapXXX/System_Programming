#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <string>

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

HWND hStart;

void StartProcess(const TCHAR* exeName)
{
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (!CreateProcess(NULL, (LPWSTR)exeName, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        MessageBox(NULL, TEXT("Failed to start process"), TEXT("Error"), MB_OK | MB_ICONERROR);
    }
    else
    {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        hStart = GetDlgItem(hWnd, IDC_BUTTON1);
        return TRUE;

    case WM_COMMAND:
        if (wParam == IDC_BUTTON1)
        {
            HANDLE hMutex = CreateMutex(NULL, FALSE, TEXT("{9509D0D4-3552-4E02-B278-6A6E8F97206B}"));

            if (hMutex == NULL)
            {
                MessageBox(NULL, TEXT("Failed to create mutex"), TEXT("Error"), MB_OK | MB_ICONERROR);
                return TRUE;
            }

            StartProcess(TEXT("Write.exe"));
            StartProcess(TEXT("Read.exe"));

            CloseHandle(hMutex);
        }
        return TRUE;

    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }

    return FALSE;
}
