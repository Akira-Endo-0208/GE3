#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include<string>

#pragma comment(lib, "d3dcompiler.lib")

using namespace Microsoft::WRL;
using namespace DirectX;

//スプライト共通部
class SpriteCommon
{

public:
	//初期化
	void Initialize(DirectXCommon* dxCommon);

	void PreDraw();

	DirectXCommon* GetDirectXCommon() { return dxcommon_; }

private:
	DirectXCommon* dxcommon_;

	// パイプランステートの生成
	ComPtr<ID3D12PipelineState> pipelineState;

	// ルートシグネチャは、テクスチャや定数バッファなどシェーダーに渡すリソースの情報をまとめたオブジェクト。
	ComPtr<ID3D12RootSignature> rootSignature;


	//テクスチャバッファの生成
	ComPtr<ID3D12Resource> texBuff;

	ComPtr<ID3D12DescriptorHeap> srvHeap;
};

