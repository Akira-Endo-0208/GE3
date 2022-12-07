#include "WinApp.h"

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//メッセージで分岐
	switch (msg) {
	case WM_DESTROY: //ウィンドウが破棄された
		PostQuitMessage(0); //OSに対して、アプリの終了を伝える
		return 0;
	}
	return DefWindowProc(hwnd,msg,wparam,lparam); //標準の処理を行う
}

void WinApp::Initialize()
{
	
	
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = (WNDPROC)WindowProc;
	wndClass.lpszClassName = L"DirectXGame";
	wndClass.hInstance = GetModuleHandle(nullptr);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wndClass);

	RECT wrc = { 0, 0, window_width,window_height };

	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	hwnd = CreateWindow(wndClass.lpszClassName,
		L"DirectXGame",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		wndClass.hInstance,
		nullptr);

	ShowWindow(hwnd, SW_SHOW);

	MSG msg{}; // メッセージ
}

void WinApp::Update()
{

}

