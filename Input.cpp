#include "Input.h"

void Input::Initialize(HINSTANCE hInstance, HWND hwnd) {
#pragma region DirectInput�֘A

	HRESULT result;

	//DirectInput�̏�����
	
	result = DirectInput8Create(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard); //�W���`��
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

#pragma endregion

}

void Input::Update() {
	HRESULT result;

	//�O��̃L�[���͂�ۑ�
	memcpy(prevKey, key, sizeof(key));

	result = keyboard->Acquire();
	
	result = keyboard->GetDeviceState(sizeof(key), key);

}

bool Input::PushKey(BYTE keyNumber)
{
	
	//�w��L�[�������Ă����true��Ԃ�
	if (key[keyNumber])
	{
		return true;
	}
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (!prevKey[keyNumber] && key[keyNumber])
	{
		return true;
	}
	return false;
}