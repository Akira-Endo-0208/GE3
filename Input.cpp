#include "Input.h"

void Input::Initialize(HINSTANCE hInstance, HWND hwnd) {
#pragma region DirectInput関連

	HRESULT result;

	//DirectInputの初期化
	
	result = DirectInput8Create(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard); //標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

#pragma endregion

}

void Input::Update() {
	HRESULT result;

	//前回のキー入力を保存
	memcpy(prevKey, key, sizeof(key));

	result = keyboard->Acquire();
	
	result = keyboard->GetDeviceState(sizeof(key), key);

}

bool Input::PushKey(BYTE keyNumber)
{
	
	//指定キーを押していればtrueを返す
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