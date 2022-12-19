#include "DirectXCommon.h"
#include "Input.h"
#include "WinApp.h"


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

	Input* input = nullptr;
	//入力の初期化
	input = new Input();
	input->Initialize(winApp);
	

#pragma endregion 
#pragma region 最初のシーンの初期化

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


#pragma endregion

		dxCommon->PreDraw();
#pragma region 最初のシーンの描画


#pragma endregion
		
		dxCommon->PostDraw();


	}
#pragma region 基盤システムの終了
	delete input;
	delete dxCommon;
	winApp->Finalize();
	delete winApp;
#pragma endregion

	return 0;
}
