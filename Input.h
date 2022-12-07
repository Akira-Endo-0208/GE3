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
	//namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	//������
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//�X�V
	void Update();
	//�L�[��������Ă��邩�`�F�b�N
	bool PushKey(BYTE keyNumber);
	//�L�[�̃g���K�[���`�F�b�N
	bool TriggerKey(BYTE keyNumber);
private:

	ComPtr<IDirectInput8> directInput;

	ComPtr<IDirectInputDevice8> keyboard;

	BYTE key[256] = {};
	BYTE prevKey[256] = {};

};

