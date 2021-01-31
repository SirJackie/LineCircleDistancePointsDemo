﻿#include <Windows.h>
#include <d3d9.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
#include "../Main.h"
#include "../CrossBufferLayer/CrossBuffer.h"


/*
** Definitions
*/

/* Define Structure*/
struct Window {
	int ScreenX;
	int ScreenY;
	int Unit;
	int Width;
	int Height;
	int LeftMargin;
	int TopMargin;
};

/* Define Variables*/
IDirect3D9* pDirect3D;
IDirect3DDevice9* pDevice;
IDirect3DSurface9* pBackBuffer;
D3DLOCKED_RECT rect;
BOOL FirstTimeRunning = TRUE;
clock_t lastTime = clock();
clock_t thisTime = clock();
Window win;
FrameBuffer fb;
Keyboard kb = (Keyboard)malloc(256 * sizeof(int));

/* Define Functions */
void GetScreenResolution(int* resultX, int* resultY) {
	// Get Screen HDC
	HDC hdcScreen;
	hdcScreen = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	// Get X and Y
	*resultX = GetDeviceCaps(hdcScreen, HORZRES);
	*resultY = GetDeviceCaps(hdcScreen, VERTRES);
	// Release HDC
	if (NULL != hdcScreen) DeleteDC(hdcScreen);
}


/*
** Message Loop
*/

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		kb[wParam] = 1;
		if (wParam == KEY_ESCAPE) {
			PostQuitMessage(0);
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_KEYUP:
		kb[wParam] = 0;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_LBUTTONDOWN:
		kb[KEY_MOUSE_LBTN] = 1;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_LBUTTONUP:
		kb[KEY_MOUSE_LBTN] = 0;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_RBUTTONDOWN:
		kb[KEY_MOUSE_RBTN] = 1;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_RBUTTONUP:
		kb[KEY_MOUSE_RBTN] = 0;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_MOUSEMOVE:
		/* Get Mouse Position */
		LOWORD(lParam);  // MouseX
		HIWORD(lParam);  // MouseY
		return DefWindowProc(hWnd, msg, wParam, lParam);

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}


/*
** Main Function
*/

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// Zeromemory the kb
	memset(kb, 0, 256 * sizeof(int));

	// Get Present Time
	thisTime = clock();
	lastTime = thisTime;

	// Calculate Window Size
	GetScreenResolution(&(win.ScreenX), &(win.ScreenY));
	win.Unit    = win.ScreenY / 30;
	win.Height  = 26 * win.Unit;
	win.Width   = win.Height / 9 * 16;
	win.LeftMargin = (win.ScreenX - win.Width)  / 2;
	win.TopMargin  = (win.ScreenY - win.Height) / 2;

	// Regist Window Class
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0, 0,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		WindowClassName, NULL
	};
	wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wc.hIcon   = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CROSSBUFFERFORWINDOWS));
	RegisterClassEx(&wc);

	// Create Window
	RECT wr;
	wr.left   = win.LeftMargin;
	wr.right  = win.Width  + wr.left;
	wr.top    = win.TopMargin;
	wr.bottom = win.Height + wr.top;
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hWnd = CreateWindowW(
		WindowClassName, WindowTitle,
		WS_OVERLAPPEDWINDOW,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		NULL, NULL, wc.hInstance, NULL
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	// Initialize Direct3D Objects
	pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,
		&d3dpp, &pDevice
	);

	// Process Messages From Windows
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		// If there is a Message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		/* Else, Process the Game Loop */
		else
		{
			/*
			** Main Loop
			*/
			
			// Get Present Time
			thisTime = clock();

			// Clear & Get Back Buffer
			pDevice->Clear(
				0, NULL, D3DCLEAR_TARGET,
				D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0
			);
			pBackBuffer = NULL;
			pDevice->GetBackBuffer(
				0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer
			);
			pBackBuffer->LockRect(&rect, NULL, NULL);

			// Init FrameBuffer Object
			fb.Width = win.Width;
			fb.Height = win.Height;

			// If it is the First Time Running
			if (FirstTimeRunning) {
				fb.pBits = rect.pBits;
				fb.Pitch = rect.Pitch;
				Setup(fb, kb, 0);                      /* Call the Setup() in Main.h */
				FirstTimeRunning = FALSE;
			}

			// If it is not the First Time Running
			else {
				fb.pBits = rect.pBits;
				fb.Pitch = rect.Pitch;
				Update(fb, kb, thisTime - lastTime);   /* Call the Update() in Main.h */
			}

			// Release Back Buffer and Swap it to Front
			pBackBuffer->UnlockRect();
			pBackBuffer->Release();
			pDevice->Present(NULL, NULL, NULL, NULL);

			// Calculate the Delta Time
			// lastTime in next frame = thisTime in this frame
			lastTime = thisTime;
		}
	}


	/*
	** After the Main Loop
	*/

	// Release All the Variables
	UnregisterClass(WindowClassName, wc.hInstance);
	if (pDevice)
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if (pDirect3D)
	{
		pDirect3D->Release();
		pDirect3D = NULL;
	}
	return 0;
}