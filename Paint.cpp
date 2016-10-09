// Paint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Paint.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE		hInst;								// current instance
WCHAR			szTitle[MAX_LOADSTRING];            // The title bar text
WCHAR			szWindowClass[MAX_LOADSTRING];      // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void				CreateMessageHandler(HWND);
void				PaintMessageHandler(HWND);
bool				CommandMessageHandler(HWND, WPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		CreateMessageHandler(hWnd);
		break;

	case WM_LBUTTONDOWN:
		ToolManager::instance->tool->MouseLButtonDown(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_MOUSEMOVE:
		ToolManager::instance->tool->MouseMove(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_LBUTTONUP:
		ToolManager::instance->tool->MouseLButtonUp(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_COMMAND: {
		bool result = CommandMessageHandler(hWnd, wParam);

		if (!result) {
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	} break;

	case WM_PAINT:
		PaintMessageHandler(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
    return 0;
}

void CreateMessageHandler(HWND hWnd) {
	Layers::Init(hWnd);
	ToolManager::Init();
}

bool CommandMessageHandler(HWND hWnd, WPARAM wParam) {
	bool result = true;
	int wmId = LOWORD(wParam);

	switch (wmId)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;

	case ID_TOOLS_NONE:
		ToolManager::instance->SetTool(TID_TOOL);
		break;

	case ID_TOOLS_PENSIL:
		ToolManager::instance->SetTool(TID_PENSIL);
		break;

	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;

	default:
		result = false;
	}

	return result;
}

void PaintMessageHandler(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	RECT r;
	GetClientRect(hWnd, &r);

	BitBlt(hdc, 0, 0, r.right, r.bottom, Layers::instance->main, 0, 0, SRCCOPY);

	EndPaint(hWnd, &ps);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
