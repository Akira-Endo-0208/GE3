#include "WinApp.h"

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//���b�Z�[�W�ŕ���
	switch (msg) {
	case WM_DESTROY: //�E�B���h�E���j�����ꂽ
		PostQuitMessage(0); //OS�ɑ΂��āA�A�v���̏I����`����
		return 0;
	}
	return DefWindowProc(hwnd,msg,wparam,lparam); //�W���̏������s��
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

	MSG msg{}; // ���b�Z�[�W
}

void WinApp::Update()
{

}

