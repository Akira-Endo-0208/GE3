#pragma once

#include<Windows.h>

class WinApp
{
public:	//メンバ関数

	//getter
	HWND GetHwnd() const { return hwnd_; }
	HINSTANCE GetHInstance() const { return wndClass_.hInstance; }

	//初期化
	void Initialize();
	//更新
	void Update();
	//終了
	void Finalize();
public: //静的メンバ関数

	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private: //メンバ変数

	//ウィンドウハンドル
	HWND hwnd_ = nullptr;
	//ウィンドウクラスの設定
	WNDCLASSEX wndClass_{};

	
public:	//定数
	static const int window_width = 1280;
	static const int window_height = 720;
};

