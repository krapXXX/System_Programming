#include "ProgressControlDlg.h"
using namespace std;
CProgressControlDlg* CProgressControlDlg::ptr = NULL;

CProgressControlDlg::CProgressControlDlg(void)
{
    ptr = this;
}

CProgressControlDlg::~CProgressControlDlg(void)
{
    if (hThread)
    {
        TerminateThread(hThread, 0);
        CloseHandle(hThread);
        hThread = nullptr;
    }
}

void CProgressControlDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}


DWORD WINAPI Thread(LPVOID lp)
{
    CProgressControlDlg* dlg = (CProgressControlDlg*)lp;

    
    ifstream inFile("file1.txt", ios::binary);
    ofstream outFile("file2.txt", ios::binary | ios::trunc);

    
    inFile.seekg(0, ios::end);
    int totalSize = inFile.tellg();
    inFile.seekg(0, ios::beg); 

    if (totalSize == 0)
    {
        MessageBox(NULL, TEXT("file1.txt is empty!"), TEXT("Warning"), MB_OK | MB_ICONWARNING);
        inFile.close();
        outFile.close();
        return 0;
    }

    const int buffSize = 20; 
    char buff[buffSize];
    int totalCopied = 0;

    while (true)
    {
        if (dlg->isPaused)
        {
            Sleep(100); 
            continue;
        }

        inFile.read(buff, buffSize);
        int copied = inFile.gcount(); 

        if (copied == 0)
            break;

        outFile.write(buff, copied);
        totalCopied += copied;

        int progress = (totalCopied * 100) / totalSize; 
        SendMessage(dlg->hProgressBar, PBM_SETPOS, progress, 0);

        Sleep(10); 
    }

    inFile.close();
    outFile.close();

    MessageBox(NULL, TEXT("File transfer completed successfully!"), TEXT("Success"), MB_OK);

    return 0;
}



BOOL CProgressControlDlg::Cls_OnInitDialog(HWND hWnd) 
{
    hEdit1 = GetDlgItem(hWnd, IDC_EDIT1);
    hEdit2 = GetDlgItem(hWnd, IDC_EDIT2);
    SetWindowText(hEdit1, TEXT("File2.txt"));
    SetWindowText(hEdit2, TEXT("File1.txt"));
    hWndDlg = hWnd;
    hProgressBar = GetDlgItem(hWnd, IDC_PROGRESS1);
    SendMessage(hProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
    SendMessage(hProgressBar, PBM_SETSTEP, 1, 0);
    return TRUE;
}

void CProgressControlDlg::Cls_OnCommand(HWND hWnd, HWND hwndFocus, WPARAM wParam) 
{
    switch (LOWORD(wParam)) 
    {
    case IDC_BUTTON1:
        if (!hThread) 
        {
            isPaused = false;
            hThread = CreateThread(NULL, 0, Thread, this, 0, NULL);
        }
        else if (isPaused) 
        {
            isPaused = false;
        }
        break;
    case IDC_BUTTON2:
        if (hThread)
        {
            if (isPaused)
            {
                ResumeThread(hThread);
                isPaused = false;
            }
            else
            {
                SuspendThread(hThread);
                isPaused = true;
            }
        }
        break;
    case IDC_BUTTON3:
        if (hThread) 
        {
            TerminateThread(hThread, 0);
            CloseHandle(hThread);
            hThread = NULL;
            ofstream outFile("file2.txt", ios::trunc);
            outFile.close();
            SendMessage(hProgressBar, PBM_SETPOS, 0, 0);
        }
        break;
    }
}

BOOL CALLBACK CProgressControlDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
    switch (message)
    {
    case WM_CLOSE:
        ptr->Cls_OnClose(hwnd);
        break;
    case WM_INITDIALOG:
        ptr->Cls_OnInitDialog(hwnd);
        break;
    case WM_COMMAND:
        ptr->Cls_OnCommand(hwnd, (HWND)lParam, wParam);
        break;
    default:
        return FALSE;
    }
    return TRUE;
}
