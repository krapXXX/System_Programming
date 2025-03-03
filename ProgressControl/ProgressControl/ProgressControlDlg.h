#pragma once
#include <windows.h>
#include <ctime>
#include <tchar.h>
#include<commctrl.h>
#include <windowsX.h>
#include "resource.h"
#include <fstream>

class CProgressControlDlg {
private:
    HWND hWndDlg;
   
public: 
    HWND hProgressBar;
HANDLE hThread;
    bool isPaused;
    HWND hProgress, hEdit1,hEdit2;
    static CProgressControlDlg* ptr;
    CProgressControlDlg(void);
    ~CProgressControlDlg(void);
    BOOL Cls_OnInitDialog(HWND hWnd);
    void Cls_OnCommand(HWND hWnd, HWND hwndFocus, WPARAM wParam);
    void Cls_OnClose(HWND hWnd);
    static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
};
