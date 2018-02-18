#include <Windows.h>
#include <tchar.h>

#define szClassName _T("IDD_VANILLA_DIALOG")
#define szAppName _T("Simple Dialog Window")

#define IDM_DIALOG_MENU 101

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int);
ATOM DialogRegisterClass(HINSTANCE);
LRESULT CALLBACK DialogWndProc(HWND,UINT,WPARAM,LPARAM);

