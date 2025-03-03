#include "ProgressControlDlg.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	CProgressControlDlg dlg;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DLGPROC(CProgressControlDlg::DlgProc));
}