#include "DirectXCommon.h"
#include "Input.h"
#include "WinApp.h"
#include "Sprite.h"
#include "SpriteCommon.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

#pragma region ��ՃV�X�e���̏�����

	HRESULT result;

	WinApp* winApp = nullptr;
	//WindowAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();
	
	DirectXCommon* dxCommon = nullptr;
	//DirectX�̏�����
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	SpriteCommon* spriteCommon = nullptr;
	//�X�v���C�g���ʕ��̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);
	spriteCommon->LoadTexture(0, "umamusume.png");
	spriteCommon->LoadTexture(1, "test.PNG");

	Input* input = nullptr;
	//���͂̏�����
	input = new Input();
	input->Initialize(winApp);
	

#pragma endregion 
#pragma region �ŏ��̃V�[���̏�����
	Sprite* sprite = new Sprite();
	sprite->Initialize(spriteCommon);
	sprite->SetTextureIndex(1);
#pragma endregion

#pragma endregion ��ՃV�X�e���̍X�V
	while (true) //�Q�[�����[�v
	{
		//Windows�̃��b�Z�[�W����
		if (winApp->ProcessMesseage()) {
			break;
		}


		
		input->Update();
		
#pragma endregion


#pragma region �ŏ��̃V�[���̍X�V
		XMFLOAT2 pos = sprite->GetPosition();
		pos.x += 0.1f;
		sprite->SetPosition(pos);
		/*XMFLOAT2 size = sprite->GetSize();
		size.x += 2.0f;
		size.y += 1.0f;
		sprite->SetSize(size);*/
		sprite->Update();
#pragma endregion

		dxCommon->PreDraw();
#pragma region �ŏ��̃V�[���̕`��
		spriteCommon->PreDraw();

		sprite->Draw();

		spriteCommon->PostDraw();
#pragma endregion
		
		dxCommon->PostDraw();


	}
#pragma region ��ՃV�X�e���̏I��
	delete input;
	delete dxCommon;
	delete spriteCommon;
	delete sprite;
	winApp->Finalize();
	delete winApp;
#pragma endregion

	return 0;
}
