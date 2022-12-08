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
	//namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	//������
	void Initialize(WinApp* winApp);
	//�X�V
	void Update();
	//�L�[��������Ă��邩�`�F�b�N
	bool PushKey(BYTE keyNumber);
	//�L�[�̃g���K�[���`�F�b�N
	bool TriggerKey(BYTE keyNumber);
private:

	ComPtr<IDirectInput8> directInput_;

	ComPtr<IDirectInputDevice8> keyboard_;

	BYTE key_[256] = {};
	BYTE prevKey_[256] = {};

	//WindowsAPI
	WinApp* winApp_ = nullptr;
};

