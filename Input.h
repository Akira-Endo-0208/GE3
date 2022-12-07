#pragma once

#include<cassert>
#include<wrl.h>
#include<dinput.h>
#include<windows.h>
#define DIRECTINPUT_VERSION		0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Microsoft::WRL;

class Input
{
public:

	//初期化
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//更新
	void Update();
};

