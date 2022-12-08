#include "Input.h"

void Input::Initialize(WinApp* winApp) {
#pragma region DirectInput�֘A

	HRESULT result;

	//�؂�Ă���WinApp�̃C���X�^���X���L�^
	this->winApp_ = winApp;

	//DirectInput�̏�����
	
	result = DirectInput8Create(
		winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput_, nullptr);
	assert(SUCCEEDED(result));

	
	result = directInput_->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = keyboard_->SetDataFormat(&c_dfDIKeyboard); //�W���`��
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = keyboard_->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

#pragma endregion

}

void Input::Update() {
	HRESULT result;

	//�O��̃L�[���͂�ۑ�
	memcpy(prevKey_, key_, sizeof(key_));

	result = keyboard_->Acquire();
	
	result = keyboard_->GetDeviceState(sizeof(key_), key_);

}

bool Input::PushKey(BYTE keyNumber)
{
	
	//�w��L�[�������Ă����true��Ԃ�
	if (key_[keyNumber])
	{
		return true;
	}
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (!prevKey_[keyNumber] && key_[keyNumber])
	{
		return true;
	}
	return false;
}