#pragma once
#include "SpriteCommon.h"
#include <DirectXMath.h>

using namespace DirectX;
using namespace Microsoft::WRL;

class Sprite
{
//�\����
public:
	//���_�f�[�^�\����
	struct Vertex
	{
		XMFLOAT3 pos;
		XMFLOAT2 uv;
	};

	//�萔�o�b�t�@(�}�e���A��)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;
	};

	struct ConstBufferDataTransform {
		XMMATRIX mat;
	};
	
public:

	//������
	void Initialize(SpriteCommon* spriteCommon);

	void Update();

	void Draw();
private:
	SpriteCommon* spriteCommon_ = nullptr;

	XMFLOAT4 color = { 1,0,0,0.5f };

	float rotationZ;
	XMFLOAT3 position;

	//���[���h�ϊ��s��
	XMMATRIX matWorld;
	XMMATRIX matRot;
	XMMATRIX matTrans;

	XMMATRIX matProjection;

	ComPtr<ID3D12Resource> vertBuff;

	D3D12_VERTEX_BUFFER_VIEW vbView{};

	ComPtr<ID3D12Resource> constBuffMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	ComPtr<ID3D12Resource> constBufferTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;

};

