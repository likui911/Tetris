// Tetris.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Tetris.h"
#include "Game.h"
#include "View.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

Game* pGame;
View* pView;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TETRIS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TETRIS));

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

	delete pView;
	delete pGame;
	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TETRIS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TETRIS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
		CW_USEDEFAULT, 0, 351, 465, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	pView = new View();
	if (!SUCCEEDED(pView->Initial(hWnd)))
	{
		return FALSE;
	}
	pView->InitialRectLCD();
	pGame = new Game(pView);
	SetTimer(hWnd, IDT_TIMER, 1000, (TIMERPROC)NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
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
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		pGame->UpdateView();
	}
	break;
	case WM_SIZE:
	{
		int width = LOWORD(lParam);
		int height = HIWORD(lParam);

		pView->Resize(width, height);
	}
	break;
	case WM_SIZING:
	{
		RECT* pRect = (RECT*)lParam;
		int width = pRect->right - pRect->left;
		int height = pRect->bottom - pRect->top;
		if (width < (int)MINIMUM_WIDTH)
		{
			pRect->right = pRect->left + (int)MINIMUM_WIDTH;
		}
		if (height < (int)MINIMUM_HEIGHT)
		{
			pRect->bottom = pRect->top + (int)MINIMUM_HEIGHT;
		}
	}
	break;
	case WM_KEYDOWN:
		if (!pGame->GameOver())
		{
			switch (wParam)
			{
			case VK_UP:
				pGame->UpArrowKey();
				break;
			case VK_DOWN:
				if (pGame->CanMoveDown())
					pGame->DownArrowKey();
				else
					pGame->MergeFigureToGrid();
				break;
			case VK_LEFT:
				pGame->LeftArrowKey();
				break;
			case VK_RIGHT:
				pGame->RightArrowKey();
				break;
			case VK_SPACE:
				while (pGame->CanMoveDown())
				{
					pGame->DownArrowKey();
					pGame->UpdateView();
				}
				pGame->MergeFigureToGrid();
				break;
			}
			pGame->UpdateView();
		}
		break;
	case WM_TIMER:
		if (!pGame->GameOver())
		{
			if (pGame->CanMoveDown())
				pGame->Timer();
			else
				pGame->MergeFigureToGrid();
			pGame->UpdateView();

			SetTimer(hWnd, IDT_TIMER, 1000 - pGame->GetLevel() * 10, (TIMERPROC)NULL);
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, IDT_TIMER);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}