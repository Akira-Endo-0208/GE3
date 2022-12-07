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
	
	
	wndClass_.cbSize = sizeof(WNDCLASSEX);
	wndClass_.lpfnWndProc = (WNDPROC)WindowProc;
	wndClass_.lpszClassName = L"DirectXGame";
	wndClass_.hInstance = GetModuleHandle(nullptr);
	wndClass_.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wndClass_);

	RECT wrc = { 0, 0, window_width,window_height };

	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	hwnd_ = CreateWindow(wndClass_.lpszClassName,
		L"DirectXGame",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		wndClass_.hInstance,
		nullptr);

	ShowWindow(hwnd_, SW_SHOW);

	MSG msg{}; // メッセージ
}

void WinApp::Update()
{

}

void WinApp::Finalize()
{
	//ウィンドウクラスを登録解除
	UnregisterClass(wndClass_.lpszClassName, wndClass_.hInstance);
}

