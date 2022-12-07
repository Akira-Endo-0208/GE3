#pragma once
#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <dinput.h>
#include <DirectXTex.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION 0x0800


#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


using namespace DirectX;
using namespace Microsoft::WRL;


struct ConstBufferDataTransform {
	XMMATRIX mat;
};




class object3D
{
public:

	void InitializeObject3d(ID3D12Device* device);

	void UpdateObject3d (XMMATRIX& matView, XMMATRIX& matProjection);

	void DrawObject3d(ID3D12GraphicsCommandList* commandList,D3D12_VERTEX_BUFFER_VIEW& vbView,D3D12_INDEX_BUFFER_VIEW& ibView, UINT numIndices);

public:

	
	

	//�萔�o�b�t�@(�s��p)
	ComPtr<ID3D12Resource> constBuffTransform;

	//�萔�o�b�t�@�}�b�v(�s��p)
	ConstBufferDataTransform* constMapTransform;

	//�A�t�B���ϊ��s��
	XMFLOAT3 scale = { 1.0f,1.0f,1.0f };
	XMFLOAT3 rotation = { 0.0f,0.0f,0.0f };
	XMFLOAT3 position = { 0.0f,0.0f,0.0f };

	XMMATRIX matScale;  //�X�P�[�����O�s��
	XMMATRIX matRot;	//��]�s��
	XMMATRIX matTrans;	//���s�ړ��s��

	//���[���h�ϊ��s��
	XMMATRIX matWorld;
	//�e�I�u�W�F�N�g�ւ̃|�C���^
	object3D* parent = nullptr;
	
	
};

