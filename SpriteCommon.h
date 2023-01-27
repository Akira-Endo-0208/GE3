#pragma once
#include "DirectXCommon.h"
#include <d3dcompiler.h>
#include<string>

#pragma comment(lib, "d3dcompiler.lib")

using namespace Microsoft::WRL;


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
};

