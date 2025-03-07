#include <windows.h>
#include <tchar.h>
#include <fstream>  
#include "resource.h"
using namespace std;
class WriteReadDlg 
{
public:
    static WriteReadDlg* ptr;

    WriteReadDlg();
    ~WriteReadDlg();

    static BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
    BOOL Cls_OnInitDialog(HWND);
    void Cls_OnCommand(HWND hWnd, HWND hwndFocus, WPARAM wParam);
    void Cls_OnClose(HWND);

    static DWORD WINAPI WriteFiles(LPVOID);
    static DWORD WINAPI ReadFiles(LPVOID);

    HWND hEdit;
};