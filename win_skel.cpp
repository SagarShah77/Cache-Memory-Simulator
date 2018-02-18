#include "win_skel.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine, int iCmdShow)
{
     MSG msg;
     HWND hWinMainWnd;
     TCHAR szNoRegister[]=_T("Unable To Register Window Class! Operation Cancelled.");
	
    if(!DialogRegisterClass(hInstance))
    {
         MessageBox(GetDesktopWindow(),szNoRegister,szAppName,MB_ICONERROR);
         return FALSE;
    }

     hWinMainWnd=CreateDialog(hInstance, szClassName, 0, NULL);

     ShowWindow(hWinMainWnd, iCmdShow);
     UpdateWindow(hWinMainWnd);

     while(GetMessage(&msg, NULL, 0, 0))
     {
	TranslateMessage(&msg);
	DispatchMessage(&msg);
     }

     return (int)msg.wParam;
}

ATOM DialogRegisterClass(HINSTANCE hInst)
{
     WNDCLASSEX wcex;

     wcex.cbSize = sizeof(WNDCLASSEX);
     wcex.style = CS_HREDRAW | CS_VREDRAW;
     wcex.lpfnWndProc = DialogWndProc;
     wcex.cbClsExtra	 = 0;
     wcex.cbWndExtra = DLGWINDOWEXTRA; // this required if dialog box is main window
     wcex.hInstance	= hInst;
     wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
     wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
     wcex.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
     wcex.lpszMenuName = MAKEINTRESOURCE(IDM_DIALOG_MENU);
     wcex.lpszClassName = szClassName;
     wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	
     return RegisterClassEx(&wcex);
	
}

LRESULT CALLBACK DialogWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_CREATE:
		return FALSE;

	case WM_COMMAND:
	case WM_SYSCOMMAND:
	switch(LOWORD(wParam))
	{
		case IDOK:
		case IDCANCEL:
		     PostQuitMessage(0);
		     return 0;
	}
	break;

	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return DefWindowProc(hwnd, message, wParam, lParam);
}
