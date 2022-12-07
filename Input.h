#pragma once

#include<cassert>
#include<wrl.h>

#define DIRECTINPUT_VERSION		0x0800
#include<dinput.h>
#include<windows.h>


#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


class Input
{
public:
	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	//初期化
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//更新
	void Update();
	//キーが押されているかチェック
	bool PushKey(BYTE keyNumber);
	//キーのトリガーをチェック
	bool TriggerKey(BYTE keyNumber);
private:

	ComPtr<IDirectInput8> directInput;

	ComPtr<IDirectInputDevice8> keyboard;

	BYTE key[256] = {};
	BYTE prevKey[256] = {};

};

