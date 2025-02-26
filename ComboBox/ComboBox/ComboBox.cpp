#include <windows.h>
#include <tchar.h>
#include "resource.h"

HWND hCombo, hList, hEdit, hC, hPS, hJS;
int subjectIndex, studentIndex, groupIndex, studentData;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
LPCTSTR students[4][3] = {
   { TEXT("Alexander Carter"), TEXT("Emma Johnson"), TEXT("Liam Smith") },
   { TEXT("Sophia Brown"), TEXT("Mason Davis"), TEXT("Olivia Wilson") },
   { TEXT("Lucas Moore"), TEXT("Ava Taylor"), TEXT("Ethan Anderson") },
   { TEXT("Charlotte Thomas"), TEXT("James White"), TEXT("Amelia Harris") } };
int marks[4][3][3] = {
{ {85, 90, 78}, {88, 76, 95}, {92, 81, 87} },
{ {75, 89, 90}, {91, 83, 77}, {80, 85, 88} },
{ {88, 79, 92}, {76, 95, 85}, {90, 91, 89} },
{ {82, 88, 80}, {94, 77, 91}, {79, 85, 88} } };


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        hCombo = GetDlgItem(hWnd, IDC_COMBO1);
        hEdit = GetDlgItem(hWnd, IDC_EDIT1);
        hList = GetDlgItem(hWnd, IDC_LIST1);

        SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("KH-P-231")));
        SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("KH-D-231")));
        SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("KH-241")));
        SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("KH-242")));
        return TRUE;
    case WM_COMMAND:
       
        if (wParam == IDC_BUTTON1)
        {
            EndDialog(hWnd, 0);
            return TRUE;
        }
        if (LOWORD(wParam) == IDC_COMBO1 && HIWORD(wParam) == CBN_SELCHANGE)
        {
            SendMessage(hList, LB_RESETCONTENT, 0, 0);
            int groupIndex = SendMessage(hCombo, CB_GETCURSEL, 0, 0);

            for (int i = 0; i < 3; i++)
            {
                studentIndex = SendMessage(hList, LB_ADDSTRING, 0, LPARAM(students[groupIndex][i]));
                SendMessage(hList, LB_SETITEMDATA, studentIndex, i);
            }
        }
        if (LOWORD(wParam) == IDC_LIST1 && HIWORD(wParam) == LBN_SELCHANGE)
        {
             studentIndex = SendMessage(hList, LB_GETCURSEL, 0, 0);
             groupIndex = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
             studentData = SendMessage(hList, LB_GETITEMDATA, studentIndex, 0);
        }

            if (LOWORD(wParam) == IDC_RADIO1 || LOWORD(wParam) == IDC_RADIO2 || LOWORD(wParam) == IDC_RADIO3)
            {
                subjectIndex = (LOWORD(wParam) == IDC_RADIO1) ? 0 :(LOWORD(wParam) == IDC_RADIO2) ? 1 : 2;
                TCHAR buff[10];
                wsprintf(buff, TEXT("%d"), marks[groupIndex][studentData][subjectIndex]);
                SetWindowText(hEdit, buff);
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