// Paint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Paint.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE		hInst;								// current instance
WCHAR			szTitle[MAX_LOADSTRING];            // The title bar text
WCHAR			szWindowClass[MAX_LOADSTRING];      // the layer[0]->dc window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    PenProp(HWND, UINT, WPARAM, LPARAM);
void				CreateMessageHandler(HWND);
void				PaintMessageHandler(HWND);
void				MouseWheelHandler(HWND, WPARAM);
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

    // layer[0]->dc message loop:
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_UICONA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW - 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_UICONA));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates layer[0]->dc window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle,
	   (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) & ~WS_MAXIMIZEBOX, CW_USEDEFAULT, 0, 707,
	   500, nullptr, nullptr, hInstance, nullptr);

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
//  PURPOSE:  Processes messages for the layer[0]->dc window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the layer[0]->dc window
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

	case WM_MOUSELEAVE:
		ToolManager::instance->tool->StopPainting();
		break;

	case WM_MOUSEWHEEL:
		MouseWheelHandler(hWnd, wParam);
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
	LayerManager::Init(hWnd);
	Lens::Init();
	ToolManager::Init();
	ColorChanger::Init(hWnd);
}

bool CommandMessageHandler(HWND hWnd, WPARAM wParam) {
	bool result = true;
	int wmId = LOWORD(wParam);

	switch (wmId)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;

	case ID_FILE_NEW:
		LayerManager::instance->Clear();
		InvalidateRect(LayerManager::instance->hWin, &(LayerManager::instance->client_area), false);
		break;

	case ID_FILE_SAVE:
		LayerManager::instance->GetMetafile()->Save(L"Paint.emf");
		break;

	case ID_FILE_OPEN:
		LayerManager::instance->DrawingImage(L"Paint.emf");
		InvalidateRect(hWnd, &(LayerManager::instance->client_area), false);
		break;

	case ID_TOOLS_PENSIL:
		ToolManager::instance->SetTool(TID_PENSIL);
		break;

	case ID_TOOLS_LINE:
		ToolManager::instance->SetTool(TID_LINE);
		break;

	case ID_TOOLS_PENCOLOR:
		ColorChanger::instance->ChangePen();
		break;

	case ID_VIEW_ZOOMIN:
		Lens::instance->ZoomIn();
		InvalidateRect(hWnd, &(LayerManager::instance->client_area), false);
		break;

	case ID_VIEW_ZOOMOUT:
		Lens::instance->ZoomOut();
		InvalidateRect(hWnd, &(LayerManager::instance->client_area), false);
		break;

	case ID_VIEW_NORMALSCALE:
		Lens::instance->NormalScale();
		InvalidateRect(hWnd, &(LayerManager::instance->client_area), false);
		break;

	case ID_TOOLS_PENWIDTH:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_PENPROP), hWnd, PenProp);
		break;

	case ID_TOOLS_BRUSHCOLOR:
		ColorChanger::instance->ChangeBrush();
		break;

	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;

	default:
		result = false;
	}

	return result;
}

void MouseWheelHandler(HWND hWnd, WPARAM wParam) {
	short zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
	int fwKeys = LOWORD(wParam);
	BOOL press_ctrl = (fwKeys & MK_CONTROL) != 0;
	BOOL press_shift = (fwKeys & MK_SHIFT) != 0;

	if (zDelta > 0) {
		if (press_ctrl && !press_shift) {
			Lens::instance->ZoomIn();
		}
		if (press_shift) {
			Lens::instance->MoveRight();
		}
		if (fwKeys == 0) {
			Lens::instance->MoveTop();
		}
	} else {
		if (press_ctrl && !press_shift) {
			Lens::instance->ZoomOut();
		}
		if (press_shift) {
			Lens::instance->MoveLeft();
		}
		if (fwKeys == 0) {
			Lens::instance->MoveBotom();
		}
	}

	InvalidateRect(hWnd, &(LayerManager::instance->client_area), false);
	//UpdateWindow(hWnd);
}

void PaintMessageHandler(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	
	Lens::instance->Scaling(hdc);

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

INT_PTR CALLBACK PenProp(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			} else {
				switch (LOWORD(wParam)) {
					case IDWIDTH1:
						LayerManager::instance->SetAllPensWidth(1);
						break;

					case IDWIDTH2:
						LayerManager::instance->SetAllPensWidth(2);
						break;

					case IDWIDTH3:
						LayerManager::instance->SetAllPensWidth(3);
						break;

					case IDWIDTH4:
						LayerManager::instance->SetAllPensWidth(4);
						break;

					case IDWIDTH5:
						LayerManager::instance->SetAllPensWidth(5);
						break;

					case IDWIDTH6:
						LayerManager::instance->SetAllPensWidth(6);
						break;

					default:
						break;
				}
			}
		break;
	}
	return (INT_PTR)FALSE;
}
