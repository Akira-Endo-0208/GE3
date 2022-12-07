#include "Input.h"

void Input::Initialize(WinApp* winApp) {
#pragma region DirectInput関連

	HRESULT result;

	//借りてきたWinAppのインスタンスを記録
	this->winApp_ = winApp;

	//DirectInputの初期化
	
	result = DirectInput8Create(
		winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput_, nullptr);
	assert(SUCCEEDED(result));

	
	result = directInput_->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = keyboard_->SetDataFormat(&c_dfDIKeyboard); //標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = keyboard_->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

#pragma endregion

}

void Input::Update() {
	HRESULT result;

	//前回のキー入力を保存
	memcpy(prevKey_, key_, sizeof(key_));

	result = keyboard_->Acquire();
	
	result = keyboard_->GetDeviceState(sizeof(key_), key_);

}

bool Input::PushKey(BYTE keyNumber)
{
	
	//指定キーを押していればtrueを返す
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