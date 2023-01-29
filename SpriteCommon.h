#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include<string>

#pragma comment(lib, "d3dcompiler.lib")

using namespace Microsoft::WRL;
using namespace DirectX;

//�X�v���C�g���ʕ�
class SpriteCommon
{

public:
	//������
	void Initialize(DirectXCommon* dxCommon);

	void PreDraw();

	DirectXCommon* GetDirectXCommon() { return dxcommon_; }

private:
	DirectXCommon* dxcommon_;

	// �p�C�v�����X�e�[�g�̐���
	ComPtr<ID3D12PipelineState> pipelineState;

	// ���[�g�V�O�l�`���́A�e�N�X�`����萔�o�b�t�@�ȂǃV�F�[�_�[�ɓn�����\�[�X�̏����܂Ƃ߂��I�u�W�F�N�g�B
	ComPtr<ID3D12RootSignature> rootSignature;


	//�e�N�X�`���o�b�t�@�̐���
	ComPtr<ID3D12Resource> texBuff;

	ComPtr<ID3D12DescriptorHeap> srvHeap;
};

