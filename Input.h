#pragma once

#include<cassert>
#include<wrl.h>

#define DIRECTINPUT_VERSION		0x0800
#include<dinput.h>
#include<windows.h>
#include "WinApp.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


class Input
{
public:
	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	//初期化
	void Initialize(WinApp* winApp);
	//更新
	void Update();
	//キーが押されているかチェック
	bool PushKey(BYTE keyNumber);
	//キーのトリガーをチェック
	bool TriggerKey(BYTE keyNumber);
private:

	ComPtr<IDirectInput8> directInput_;

	ComPtr<IDirectInputDevice8> keyboard_;

	BYTE key_[256] = {};
	BYTE prevKey_[256] = {};

	//WindowsAPI
	WinApp* winApp_ = nullptr;
};

