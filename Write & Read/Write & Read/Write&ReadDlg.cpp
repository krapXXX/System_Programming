#include "Write&ReadDlg.h"

WriteReadDlg* WriteReadDlg::ptr = nullptr;
CRITICAL_SECTION cs;
int numCopies;


WriteReadDlg::WriteReadDlg()
{
	ptr = this;
	InitializeCriticalSection(&cs);
}

WriteReadDlg::~WriteReadDlg()
{
	DeleteCriticalSection(&cs);
}

DWORD WINAPI WriteReadDlg::WriteFiles(LPVOID param)
{	WriteReadDlg* dlg = (WriteReadDlg*)param;
	EnterCriticalSection(&cs);


	ifstream source("FirstFile.txt", ios::binary);


	source.seekg(0, ios::end);
	int sourceSize = source.tellg();
	source.seekg(0, ios::beg);

	char* buff = new char[sourceSize];
	source.read(buff, sourceSize);

	for (int i = 1; i <= numCopies; i++)
	{
		
		TCHAR filename[25];
		_stprintf_s(filename, TEXT("File%d.txt"), i);
		ofstream destination(filename, ios::binary);

		destination.write(buff, sourceSize);

		source.close();
		destination.close();
		
	}
	delete[]buff;
	LeaveCriticalSection(&cs);
	return 0;
}

DWORD WINAPI WriteReadDlg::ReadFiles(LPVOID param)
{
	WriteReadDlg* dlg = (WriteReadDlg*)param;
	EnterCriticalSection(&cs);
	//numCopies += 1;
	ofstream resultFile("result.txt", ios::binary);
	for (int i = 1; i <= numCopies; i++)
	{
		
		TCHAR filename[25];
		_stprintf_s(filename, TEXT("File%d.txt"), i);
		ifstream source(filename, ios::binary);

		    source.seekg(0, ios::end);
			int sourceSize = source.tellg();
			source.seekg(0, ios::beg);

			char* buff = new char[sourceSize];
			source.read(buff, sourceSize);
			resultFile.write(buff, sourceSize);

			delete[]buff;
			source.close();
	}

	MessageBox(NULL, TEXT("Files read successfully!"), TEXT("Success"), MB_OK | MB_ICONINFORMATION);
	resultFile.close();
	LeaveCriticalSection(&cs);

	return 0;
}

BOOL WriteReadDlg::Cls_OnInitDialog(HWND hwnd)
{
	hEdit = GetDlgItem(hwnd, IDC_EDIT1);
	return TRUE;
}

void WriteReadDlg::Cls_OnCommand(HWND hwnd, HWND hwndFocus, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON1:
	{
		TCHAR buff[10];
		GetDlgItemText(hwnd, IDC_EDIT1, buff, 10);
		int copies = _ttoi(buff);

		if (copies < 1 || copies > 10)
		{
			MessageBox(hwnd, TEXT("Please enter a number between 1 and 10!"), TEXT("Invalid Input"), MB_OK | MB_ICONERROR);
			SetWindowText(hEdit, NULL);
			return;
		}

		numCopies = copies;

		CreateThread(NULL, 0, WriteFiles, NULL, 0, NULL);
		CreateThread(NULL, 0, ReadFiles, NULL, 0, NULL);
		break;
	}
	}
}

void WriteReadDlg::Cls_OnClose(HWND hwnd)
{
	for (int i = 1; i <= numCopies; i++)
	{
		TCHAR filename[25];
		_stprintf_s(filename, TEXT("File%d.txt"), i);
		DeleteFile(filename); 
	}

	DeleteFile(TEXT("result.txt"));
	EndDialog(hwnd, 0);
}

BOOL CALLBACK WriteReadDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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