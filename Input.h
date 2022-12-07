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
	//namespaceÈ—ª
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	//‰Šú‰»
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//XV
	void Update();

private:
	ComPtr<IDirectInputDevice8> keyboard;
};

