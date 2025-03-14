#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <iostream>
#include <fstream>

using namespace std;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

HWND hwnd;

DWORD WINAPI ReadFromFiles(LPVOID lp)
{
    int amount = (int)lp;
    TCHAR filename[30];

    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{9509D0D4-3552-4E02-B278-6A6E8F97206B}"));
    DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);

    if (dwAnswer == WAIT_OBJECT_0)
    {
        ofstream resultFile("result.txt", ios::binary);
        for (int i = 1; i <= amount; i++)
        {
            _stprintf_s(filename, TEXT("File%d.txt"), i);
            ifstream source(filename, ios::binary);

            source.seekg(0, ios::end);
            int sourceSize = source.tellg();
            source.seekg(0, ios::beg);

            char* buff = new char[sourceSize];
            source.read(buff, sourceSize);
            resultFile.write(buff, sourceSize);

            delete[] buff;
            source.close();
        }
        MessageBox(NULL, TEXT("Files read successfully!"), TEXT("Success"), MB_OK | MB_ICONINFORMATION);
        resultFile.close();
        ReleaseMutex(hMutex);
    }

    return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        hwnd = hWnd;
        CreateThread(NULL, 0, ReadFromFiles, (LPVOID)5, 0, NULL);
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}
