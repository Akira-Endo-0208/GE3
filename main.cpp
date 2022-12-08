#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <wrl.h>
#include "object3D.h"
#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")



using namespace DirectX;
using namespace Microsoft::WRL;


LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

#ifdef _DEBUG
	//�f�o�b�O���C���[���I����
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
#endif

	HRESULT result;

	//�|�C���^�u����
	Input* input = nullptr;
	WinApp* winApp = nullptr;
	DirectXCommon* directX = nullptr;

	winApp = new WinApp();
	winApp->Initialize();
	input = new Input();
	input->Initialize(winApp);
	directX = new DirectXCommon();
	directX->Initialize();

#pragma region ���_�f�[�^

	// ���_�f�[�^�\����
	struct Vertex
	{
		XMFLOAT3 pos;
		XMFLOAT3 normal;
		XMFLOAT2 uv;
	};


	//���_�f�[�^(�������e�s��)
	Vertex vertices[] = {
		//   x      y      z       u     v
		//�O
		{{-5.0f, -5.0f, -5.0f}, {}, {0.0f, 1.0f}},
		{{-5.0f,  5.0f, -5.0f}, {}, {0.0f, 0.0f}},
		{{ 5.0f, -5.0f, -5.0f}, {}, {1.0f, 1.0f}},
		{{ 5.0f,  5.0f, -5.0f}, {}, {1.0f, 0.0f}},
		//��(�O�ʂ�Z���W�̕������t)
		{{-5.0f, -5.0f,  5.0f}, {}, {0.0f, 1.0f}},
		{{-5.0f,  5.0f,  5.0f}, {}, {0.0f, 0.0f}},
		{{ 5.0f, -5.0f,  5.0f}, {}, {1.0f, 1.0f}},
		{{ 5.0f,  5.0f,  5.0f}, {}, {1.0f, 0.0f}},
		//��					   
		{{-5.0f, -5.0f, -5.0f}, {}, {0.0f, 1.0f}},
		{{-5.0f, -5.0f,  5.0f}, {}, {0.0f, 0.0f}},
		{{-5.0f,  5.0f, -5.0f}, {}, {1.0f, 1.0f}},
		{{-5.0f,  5.0f,  5.0f}, {}, {1.0f, 0.0f}},
		//�E(���ʂ�X���W�̕������t) 
		{{ 5.0f, -5.0f, -5.0f}, {}, {0.0f, 1.0f}},
		{{ 5.0f, -5.0f,  5.0f}, {}, {0.0f, 0.0f}},
		{{ 5.0f,  5.0f, -5.0f}, {}, {1.0f, 1.0f}},
		{{ 5.0f,  5.0f,  5.0f}, {}, {1.0f, 0.0f}},
		//��					   
		{{-5.0f, -5.0f, -5.0f}, {}, {0.0f, 1.0f}},
		{{-5.0f, -5.0f,  5.0f}, {}, {0.0f, 0.0f}},
		{{ 5.0f, -5.0f, -5.0f}, {}, {1.0f, 1.0f}},
		{{ 5.0f, -5.0f,  5.0f}, {}, {1.0f, 0.0f}},
		//��(���ʂ�Y���W�̕������t)
		{{-5.0f,  5.0f, -5.0f}, {}, {0.0f, 1.0f}},
		{{-5.0f,  5.0f,  5.0f}, {}, {0.0f, 0.0f}},
		{{ 5.0f,  5.0f, -5.0f}, {}, {1.0f, 1.0f}},
		{{ 5.0f,  5.0f,  5.0f}, {}, {1.0f, 0.0f}},
	};
	unsigned short indices[] =
	{
		//�O
		0,1,2, //�O�p�`1��
		2,1,3, //�O�p�`2��
		//��(�O�̖ʂ�4���Z)
		6,5,4, //�O�p�`3��
		7,5,6, //�O�p�`4��
		//��
		8,9,10,
		10,9,11,
		//�E
		14,13,12,
		13,14,15,
		//��
		18,17,16,
		19,17,18,
		//��
		20,21,22,
		22,21,23
	};


	// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));
#pragma endregion


#pragma region �@���̎���

	for (int i = 0; i < 36 / 3; i++)
	{
		//�O�p�`�̃C���f�b�N�X�����o���āA�ꎞ�I�ȕϐ�������
		unsigned short indices0 = indices[i * 3 + 0];
		unsigned short indices1 = indices[i * 3 + 1];
		unsigned short indices2 = indices[i * 3 + 2];
		//�O�p�`���\�����钸�_���W���x�N�g���ɑ��
		XMVECTOR p0 = XMLoadFloat3(&vertices[indices0].pos);
		XMVECTOR p1 = XMLoadFloat3(&vertices[indices1].pos);
		XMVECTOR p2 = XMLoadFloat3(&vertices[indices2].pos);
		//p0��p1�x�N�g���Ap0��p2�x�N�g�����v�Z�@(�x�N�g���̌��Z)
		XMVECTOR v1 = XMVectorSubtract(p1, p0);
		XMVECTOR v2 = XMVectorSubtract(p2, p0);
		//�O�ς͗������琂���ȃx�N�g��
		XMVECTOR normal = XMVector3Cross(v1, v2);
		//���K��(������1�ɂ���)
		normal = XMVector3Normalize(normal);
		//���߂��@���𒸓_�f�[�^�ɑ��
		XMStoreFloat3(&vertices[indices0].normal, normal);
		XMStoreFloat3(&vertices[indices1].normal, normal);
		XMStoreFloat3(&vertices[indices2].normal, normal);
	}

#pragma endregion


#pragma region ���_�o�b�t�@�̃f�X�N���v�^�q�[�v�쐬

	// ���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; // ���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

#pragma endregion

#pragma region ���_�o�b�t�@�̐���

	// ���_�o�b�t�@�̐���
	ComPtr<ID3D12Resource> vertBuff;
	result = directX->GetDevice()->CreateCommittedResource(
		&heapProp, // �q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc, // ���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(result));

#pragma endregion

#pragma region �C���f�b�N�X�o�b�t�@�̐ݒ�

	//�C���f�b�N�X�f�[�^�S�̂̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * _countof(indices));
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

#pragma endregion

#pragma region �C���f�b�N�X�o�b�t�@�̐����ƃ}�b�s���O

	//�C���f�b�N�X�o�b�t�@�̐���
	ComPtr<ID3D12Resource> indexBuff;
	result = device->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&indexBuff));

	//�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//�S�C���f�b�N�X�ɑ΂���
	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];
	}
	//�}�b�s���O����
	indexBuff->Unmap(0, nullptr);


	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	// �S���_�ɑ΂���
	for (int i = 0; i < _countof(vertices); i++) {
		vertMap[i] = vertices[i]; // ���W���R�s�[
	}
	// �q���������
	vertBuff->Unmap(0, nullptr);

#pragma endregion

#pragma region �C���f�b�N�X�o�b�t�@�r���[�̍쐬

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// GPU���z�A�h���X
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	// ���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = sizeVB;
	// ���_1���̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(vertices[0]);

	ID3DBlob* vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
	ID3DBlob* psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ID3DBlob* errorBlob = nullptr; // �G���[�I�u�W�F�N�g

#pragma endregion

#pragma region ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"Resources/shaders/BasicVS.hlsl", // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&vsBlob, &errorBlob);

	// �G���[�Ȃ�
	if (FAILED(result)) {
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}

#pragma endregion

#pragma region �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��

	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"Resources/shaders/BasicPS.hlsl", // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&psBlob, &errorBlob);

	// �G���[�Ȃ�
	if (FAILED(result)) {
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}

#pragma endregion

	// ���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
	{
	"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
	D3D12_APPEND_ALIGNED_ELEMENT,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	}, // (1�s�ŏ������ق������₷��)
	{
		"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,
		D3D12_APPEND_ALIGNED_ELEMENT,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
	},
	{
	"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
	D3D12_APPEND_ALIGNED_ELEMENT,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	},
	};

	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};


	// �V�F�[�_�[�̐ݒ�
	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();

	// �T���v���}�X�N�̐ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	//���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // �w�ʂ��J�����O
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
	pipelineDesc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����


#pragma region �����_�[�^�[�Q�b�g
	// �����_�[�^�[�Q�b�g�̃u�����h�ݒ�
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA�S�Ẵ`�����l����`��

	blenddesc.BlendEnable = false;                    //�u�����h�𖳌��ɂ���
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;     //���Z
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;       //�\�[�X�̒l��100%�g��
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;     //�f�X�g�̒l��0%�g��


	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;     //
	//blenddesc.SrcBlend = D3D12_BLEND_INV_SRC_ALPHA;       //�\�[�X�̒l��100%�g��
	//blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;     //�f�X�g�̒l��0%�g��
#pragma endregion

	// ���_���C�A�E�g�̐ݒ�
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);

	// �}�`�̌`��ݒ�
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// ���̑��̐ݒ�
	pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

#pragma region �f�X�N���v�^�����W�̐ݒ�
	//�f�X�N���v�^�����W�̐ݒ�
	D3D12_DESCRIPTOR_RANGE descriptorRange{};
	descriptorRange.NumDescriptors = 1; //��x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0;
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
#pragma endregion

#pragma region �e�N�X�`���T���v���[�̐ݒ�
	//�e�N�X�`���T���v���[�̐ݒ�
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
#pragma endregion

#pragma region ���[�g�p�����[�^�̐ݒ�
	//���[�g�p�����[�^�̐ݒ�
	D3D12_ROOT_PARAMETER rootParams[3] = {};

	//�萔�o�b�t�@0��
	rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; //���
	rootParams[0].Descriptor.ShaderRegister = 0; //�萔�o�b�t�@�ԍ�
	rootParams[0].Descriptor.RegisterSpace = 0; //�f�t�H���g�l
	rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; //�S�ẴV�F�[�_���猩����

	//�e�N�X�`�����W�X�^0��
	rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; //���
	rootParams[1].DescriptorTable.pDescriptorRanges = &descriptorRange; //�f�X�N���v�^�����W
	rootParams[1].DescriptorTable.NumDescriptorRanges = 1; //�f�X�N���v�^�����W��
	rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; //�S�ẴV�F�[�_���猩����

	//�萔�o�b�t�@1��
	rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; //���
	rootParams[2].Descriptor.ShaderRegister = 1; //�萔�o�b�t�@�ԍ�
	rootParams[2].Descriptor.RegisterSpace = 0; //�f�t�H���g�l
	rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; //�S�ẴV�F�[�_���猩����
#pragma endregion

#pragma region ���[�g�V�O�l�`���̐ݒ�
	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature;
	// ���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams;
	rootSignatureDesc.NumParameters = _countof(rootParams);
	rootSignatureDesc.pStaticSamplers = &samplerDesc;
	rootSignatureDesc.NumStaticSamplers = 1;

	// ���[�g�V�O�l�`���̃V���A���C�Y
	ComPtr<ID3DBlob> rootSigBlob = nullptr;
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(result));
	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = rootSignature.Get();

#pragma endregion

	pipelineDesc.DepthStencilState.DepthEnable = true;
	pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

#pragma region �p�C�v���C���X�e�[�g�̐���
	// �p�C�v���C���X�e�[�g�̐���
	ComPtr<ID3D12PipelineState> pipelineState;
	result = device->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(result));
#pragma endregion

	//DirectX���������������܂�


	//�`��ݒ菈����������

#pragma region �`��ɕK�v�ȕϐ�
	struct ConstBufferMaterial {
		XMFLOAT4 color;
	};
	struct ConstBufferDataTransform {
		XMMATRIX mat;
	};

	ComPtr<ID3D12Resource> constBuffMaterial;
	ConstBufferMaterial* constMapMaterial = nullptr;
	ComPtr<ID3D12Resource> constBuffTransform0;
	ComPtr<ID3D12Resource> constBuffTransform1;
	ConstBufferDataTransform* constMapTransform0 = nullptr;
	ConstBufferDataTransform* constMapTransform1 = nullptr;

	const static size_t kObjectCount = 50;
	object3D object3ds[kObjectCount];
	float angle = 0.0f;
#pragma endregion

#pragma region �F�̒萔�o�b�t�@
	{

		//�q�[�v�ݒ�
		D3D12_HEAP_PROPERTIES cbHeapProp{};
		cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		//���\�[�X�ݒ�
		D3D12_RESOURCE_DESC cbResourceDesc{};
		cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		cbResourceDesc.Width = (sizeof(ConstBufferMaterial) + 0xff) & ~0xff;
		cbResourceDesc.Height = 1;
		cbResourceDesc.DepthOrArraySize = 1;
		cbResourceDesc.MipLevels = 1;
		cbResourceDesc.SampleDesc.Count = 1;
		cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;


		//�萔�o�b�t�@�̐���

		result = device->CreateCommittedResource(&cbHeapProp, D3D12_HEAP_FLAG_NONE, &cbResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&constBuffMaterial));
		assert(SUCCEEDED(result));

		//�萔�o�b�t�@�̃}�b�s���O

		result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);
		assert(SUCCEEDED(result));
		constMapMaterial->color = XMFLOAT4(1, 1, 1, 0.5f);
	}
#pragma endregion

#pragma region 3D�ϊ��s��̒萔�o�b�t�@



	for (int i = 0; i < _countof(object3ds); i++)
	{
		//������
		object3ds[i].InitializeObject3d(device.Get());
		//�擪�ȊO�Ȃ�
		if (i > 0) {
			//��O�̃I�u�W�F�N�g��e�I�u�W�F�N�g�Ƃ���
			object3ds[i].parent = &object3ds[i - 1];
			//�e�I�u�W�F�N�g��9���̑傫��
			object3ds[i].scale = { 0.9f,0.9f,0.9f };
			//�e�I�u�W�F�N�g�ɑ΂���Z���܂���30�x��]
			object3ds[i].rotation = { 0.0f,0.0f,XMConvertToRadians(30.0f) };

			//�e�I�u�W�F�N�g�ɑ΂���Z����-8.0���炷
			object3ds[i].position = { 0.0f,0.0f,-8.0f };
		}
	}

	//���s���e�s��̌v�Z
	//constMapTransform->mat = XMMatrixOrthographicOffCenterLH(
	//	-1.0f, window_width,
	//	window_height, 1.0f,
	//	0.0f, 1.0f
	//);

	//�r���[�ϊ��s��
	XMMATRIX matView;
	XMFLOAT3 eye(0, 0, -100);	//���_���W
	XMFLOAT3 target(0, 0, 0);	//�����_���W
	XMFLOAT3 up(0, 1, 0);		//������x�N�g��

	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));


	//�������e�s��̌v�Z
	XMMATRIX matProjection =
		XMMatrixPerspectiveFovLH(
			XMConvertToRadians(45.0f),
			(float)WinApp::window_width / WinApp::window_height,
			0.1f, 1000.0f
		);



	//�J�����𓮂����Ȃ��ꍇ
	/*constMapTransform->mat = matView * matProjection;*/

#pragma endregion


	ComPtr<ID3D12DescriptorHeap> basicDescHeap;
	//�ݒ�\����
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	descHeapDesc.NumDescriptors = 1;

	result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&basicDescHeap));

	D3D12_CONSTANT_BUFFER_VIEW_DESC  cbvDesc{};
	cbvDesc.BufferLocation = constBuffMaterial->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (UINT)constBuffMaterial->GetDesc().Width;

	device->CreateConstantBufferView(&cbvDesc, basicDescHeap->GetCPUDescriptorHandleForHeapStart());

#pragma region �摜�C���[�W�f�[�^�̍쐬
	////�������s�N�Z����
	//const size_t textureWidth = 256;
	////�c�����s�N�Z����
	//const size_t textureHeight = 256;
	////�z��̗v�f��
	//const size_t imageDataCount = textureWidth * textureHeight;
	////�摜�C���[�W�f�[�^�z��
	//XMFLOAT4* imageData = new XMFLOAT4[imageDataCount]; //�K����ŉ������

	////�S�s�N�Z���̐F��������
	//for (size_t i = 0; i < imageDataCount; i++)
	//{
	//	imageData[i].x = 0.7f; //R
	//	imageData[i].y = 0.7f; //G
	//	imageData[i].z = 0.7f; //B
	//	imageData[i].w = 1.0f; //A
	//}

	TexMetadata metadata{};
	ScratchImage scratchImg{};

	TexMetadata metadata2{};
	ScratchImage scratchImg2{};

	//WIC�e�N�X�`���̃��[�h
	result = LoadFromWICFile(
		L"Resources/mario.jpg",
		WIC_FLAGS_NONE,
		&metadata, scratchImg);

	result = LoadFromWICFile(
		L"Resources/reimu.png",
		WIC_FLAGS_NONE,
		&metadata2, scratchImg2);

	ScratchImage mipChain{};
	//�~�b�v�}�b�v����
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain);
	if (SUCCEEDED(result)) {
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}
	//�ǂݍ��񂾃f�B�t���[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata.format = MakeSRGB(metadata.format);


	ScratchImage mipChain2{};
	//�~�b�v�}�b�v����
	result = GenerateMipMaps(
		scratchImg2.GetImages(), scratchImg2.GetImageCount(), scratchImg2.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain2);
	if (SUCCEEDED(result)) {
		scratchImg2 = std::move(mipChain2);
		metadata2 = scratchImg2.GetMetadata();
	}
	//�ǂݍ��񂾃f�B�t���[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata2.format = MakeSRGB(metadata2.format);

#pragma endregion

#pragma region �e�N�X�`���o�b�t�@�̐���
	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty =
		D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;

	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metadata.format;
	textureResourceDesc.Width = metadata.width;
	textureResourceDesc.Height = (UINT)metadata.height;
	textureResourceDesc.DepthOrArraySize = (UINT)metadata.arraySize;
	textureResourceDesc.MipLevels = (UINT)metadata.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC textureResourceDesc2{};
	textureResourceDesc2.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc2.Format = metadata2.format;
	textureResourceDesc2.Width = metadata2.width;
	textureResourceDesc2.Height = (UINT)metadata2.height;
	textureResourceDesc2.DepthOrArraySize = (UINT)metadata2.arraySize;
	textureResourceDesc2.MipLevels = (UINT)metadata2.mipLevels;
	textureResourceDesc2.SampleDesc.Count = 1;


	//�e�N�X�`���o�b�t�@�̐���
	ComPtr<ID3D12Resource> texBuff;
	result = device->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texBuff));

	ComPtr<ID3D12Resource> texBuff2;
	result = device->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc2,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texBuff2));

	//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		//�~�b�v�}�b�v���x�����w�肵�ăC���[�W���擾
		const Image* img = scratchImg.GetImage(i, 0, 0);
		//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = texBuff->WriteToSubresource(
			(UINT)i,
			nullptr, //�S�̈�R�s�[
			img->pixels, //���f�[�^�A�h���X
			(UINT)img->rowPitch, //1���C���T�C�Y
			(UINT)img->slicePitch//�S�T�C�Y
		);
		assert(SUCCEEDED(result));
	}

	//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	for (size_t i = 0; i < metadata2.mipLevels; i++)
	{
		//�~�b�v�}�b�v���x�����w�肵�ăC���[�W���擾
		const Image* img = scratchImg2.GetImage(i, 0, 0);
		//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = texBuff2->WriteToSubresource(
			(UINT)i,
			nullptr, //�S�̈�R�s�[
			img->pixels, //���f�[�^�A�h���X
			(UINT)img->rowPitch, //1���C���T�C�Y
			(UINT)img->slicePitch//�S�T�C�Y
		);
		assert(SUCCEEDED(result));
	}

#pragma endregion

#pragma region �V�F�[�_�[���\�[�X�r���[�̃f�X�N���v�^�쐬
	//SRV�̍ő��
	const size_t kMaxSRVCount = 2056;

	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvHeapDesc.NumDescriptors = kMaxSRVCount;
#pragma endregion

#pragma region �V�F�[�_�[���\�[�X�r���[�̍쐬

	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	ComPtr<ID3D12DescriptorHeap> srvHeap;
	result = device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(srvHeap.GetAddressOf()));
	assert(SUCCEEDED(result));

	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();


	//�V�F�[�_���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; //�ݒ�\����
	srvDesc.Format = textureResourceDesc.Format;//RGBA float
	srvDesc.Shader4ComponentMapping =
		D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; //2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = textureResourceDesc.MipLevels;


	//�n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	device->CreateShaderResourceView(texBuff.Get(), &srvDesc, srvHandle);

	UINT incrementSize = device.Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	srvHandle.ptr += incrementSize;

	//�V�F�[�_���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc2{}; //�ݒ�\����
	srvDesc2.Format = textureResourceDesc2.Format;//RGBA float
	srvDesc2.Shader4ComponentMapping =
		D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc2.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; //2D�e�N�X�`��
	srvDesc2.Texture2D.MipLevels = textureResourceDesc2.MipLevels;

	//�n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	device->CreateShaderResourceView(texBuff2.Get(), &srvDesc2, srvHandle);
#pragma endregion


	while (true) //�Q�[�����[�v
	{
		//Windows�̃��b�Z�[�W����
		if (winApp->ProcessMesseage()) {
			break;
		}


		//DirectX���t���[��������������

		
		input->Update();
		


#pragma region �r���[�s��̌v�Z
		//�r���[�s��̌v�Z
		if (input->PushKey(DIK_D) || input->PushKey(DIK_A))
		{
			if (input->PushKey(DIK_D)) { angle += XMConvertToRadians(2.0f); }
			else if (input->PushKey(DIK_A)) { angle -= XMConvertToRadians(2.0f); }

			//angle���W�A������Y���܂��ɉ�]�B���a��-100
			eye.x = -100 * sinf(angle);
			eye.z = -100 * cosf(angle);
			matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

		}
#pragma endregion

#pragma region ���[���h�s��̌v�Z

		if(input->PushKey(DIK_UP)){object3ds[0].position.y += 1.0f; }
		if (input->PushKey(DIK_DOWN)) { object3ds[0].position.y -= 1.0f; }
		for (size_t i = 0; i < _countof(object3ds); i++)
		{
			object3ds[i].UpdateObject3d(matView, matProjection);
		}

#pragma endregion


		//�o�b�N�o�b�t�@�̔ԍ����擾(2�Ȃ̂�0�Ԃ�1��)
		UINT bbIndex = swapChain->GetCurrentBackBufferIndex();

		// 1.���\�[�X�o���A�ŏ������݉\�ɕύX
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = backBuffers[bbIndex].Get(); //�o�b�N�o�b�t�@���w��
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT; //�\����Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		commandList->ResourceBarrier(1, &barrierDesc);

		// 2.�`���̕ύX
		//�@�����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += bbIndex * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		//�[�x�X�e���V���r���[�p�f�X�N���v�^�q�[�v�̃n���h�����擾
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
		commandList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

		// 3. ��ʃN���A�@�@�@�@�@�@R     G    B     A
		FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f };
		commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
		commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);





		// 4.�`��R�}���h��������

		// �r���[�|�[�g�ݒ�R�}���h
		D3D12_VIEWPORT viewport{};
		viewport.Width = 1280;
		viewport.Height = 720;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		commandList->RSSetViewports(1, &viewport);


		// �V�U�[��`
		D3D12_RECT scissorRect{};
		scissorRect.left = 0; // �؂蔲�����W��
		scissorRect.right = scissorRect.left + WinApp::window_width; // �؂蔲�����W�E
		scissorRect.top = 0; // �؂蔲�����W��
		scissorRect.bottom = scissorRect.top + WinApp::window_height; // �؂蔲�����W��
		// �V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		commandList->RSSetScissorRects(1, &scissorRect);

		// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
		commandList->SetPipelineState(pipelineState.Get());
		commandList->SetGraphicsRootSignature(rootSignature.Get());

		// �v���~�e�B�u�`��̐ݒ�R�}���h
		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

		//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
		commandList->IASetIndexBuffer(&ibView);

		// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
		commandList->IASetVertexBuffers(0, 1, &vbView);

		commandList->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());

		//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
		commandList->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());
		//SRV�q�[�v�̐ݒ�R�}���h
		commandList->SetDescriptorHeaps(1, srvHeap.GetAddressOf());
		//SRV�q�[�v�̐擪�n���h�����擾
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

		if (input->TriggerKey(DIK_SPACE))
		{
			srvGpuHandle.ptr += incrementSize;
		}

		//SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
		commandList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);

		for (int i = 0; i < _countof(object3ds); i++)
		{
			object3ds[i].DrawObject3d(commandList.Get(), vbView, ibView, _countof(indices));
		}


		// 4.�`��R�}���h�����܂�


		// 5.���\�[�X�o���A��߂�
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; //�`���Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT; //�\����Ԃ�
		commandList->ResourceBarrier(1, &barrierDesc);

		//���߂̃N���[�Y
		result = commandList->Close();
		assert(SUCCEEDED(result));
		//�R�}���h���X�g�̎��s
		ID3D12CommandList* commandLists[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(1, commandLists);

		//��ʂɕ\������o�b�t�@���t���b�v(���\�̓��ւ�)
		result = swapChain->Present(1, 0);
		assert(SUCCEEDED(result));


		//�R�}���h�̎��s������҂�
		commandQueue->Signal(fence.Get(), ++fenceVal);
		if (fence->GetCompletedValue() != fenceVal)
		{
			HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			fence->SetEventOnCompletion(fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}

		//�L���[���N���A
		result = cmdAllocator->Reset();
		assert(SUCCEEDED(result));
		//�ĂуR�}���h���X�g�𒙂߂鏀��
		result = commandList->Reset(cmdAllocator.Get(), nullptr);
		assert(SUCCEEDED(result));



		//DirectX���t���[�����������܂�
	}

	winApp->Finalize();
	delete input;
	delete winApp;
	return 0;
}
