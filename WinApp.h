#pragma once

#include<Windows.h>

class WinApp
{
public:	//�����o�֐�

	//getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return wndClass.hInstance; }

	//������
	void Initialize();
	//�X�V
	void Update();

public: //�ÓI�����o�֐�

	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private: //�����o�ϐ�

	//�E�B���h�E�n���h��
	HWND hwnd = nullptr;
	//�E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX wndClass{};
public:	//�萔
	static const int window_width = 1280;
	static const int window_height = 720;
};

