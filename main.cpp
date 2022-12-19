#include "DirectXCommon.h"
#include "Input.h"
#include "WinApp.h"
#include "Sprite.h"
#include "SpriteCommon.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

#pragma region 基盤システムの初期化

	HRESULT result;

	WinApp* winApp = nullptr;
	//WindowAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();
	
	DirectXCommon* dxCommon = nullptr;
	//DirectXの初期化
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	SpriteCommon* spriteCommon = nullptr;
	//スプライト共通部の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);
	spriteCommon->LoadTexture(0, "umamusume.png");
	spriteCommon->LoadTexture(1, "test.PNG");

	Input* input = nullptr;
	//入力の初期化
	input = new Input();
	input->Initialize(winApp);
	

#pragma endregion 
#pragma region 最初のシーンの初期化
	Sprite* sprite = new Sprite();
	sprite->Initialize(spriteCommon);
	sprite->SetTextureIndex(1);
#pragma endregion

#pragma endregion 基盤システムの更新
	while (true) //ゲームループ
	{
		//Windowsのメッセージ処理
		if (winApp->ProcessMesseage()) {
			break;
		}


		
		input->Update();
		
#pragma endregion


#pragma region 最初のシーンの更新
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
#pragma region 最初のシーンの描画
		spriteCommon->PreDraw();

		sprite->Draw();

		spriteCommon->PostDraw();
#pragma endregion
		
		dxCommon->PostDraw();


	}
#pragma region 基盤システムの終了
	delete input;
	delete dxCommon;
	delete spriteCommon;
	delete sprite;
	winApp->Finalize();
	delete winApp;
#pragma endregion

	return 0;
}
