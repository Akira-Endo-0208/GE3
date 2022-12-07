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

	//‰Šú‰»
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//XV
	void Update();
};

