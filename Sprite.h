#pragma once
#include "SpriteCommon.h"
#include <DirectXMath.h>

using namespace DirectX;
using namespace Microsoft::WRL;

class Sprite
{
//構造体
public:
	//頂点データ構造体
	struct Vertex
	{
		XMFLOAT3 pos;
		XMFLOAT2 uv;
	};

	//定数バッファ(マテリアル)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;
	};

	struct ConstBufferDataTransform {
		XMMATRIX mat;
	};

	enum VertexNumber {
		LB,
		LT,
		RB,
		RT
	};
	
public:

	//初期化
	void Initialize(SpriteCommon* spriteCommon);

	void Update();

	void Draw();
	XMFLOAT4 GetColor() const { return color; }

	const XMFLOAT2 GetPosition() const { return position_; }

	const float& GetRotationZ() const { return rotationZ; }

	const XMFLOAT2 GetSize() const { return size_; }

	const XMFLOAT2 GetAnchorPoint() const { return anchorPoint_; }

	const bool& GetIsFlipX() const{ return isFlipX; }

	const bool& GetIsFlipY() const { return isFlipY; }

	const bool& GetIsInvisible() const { return isInvisible_; }


	void SetColor(XMFLOAT4 color) { this->color = color; }
	
	void SetPosition(const XMFLOAT2& position) { this->position_ = position; }

	void SetRotationZ(const float& rotationZ) { this->rotationZ = rotationZ; }

	void SetSize(const XMFLOAT2& size) { this->size_ = size; }

	void SetAnchorPoint(const XMFLOAT2& anchorPoint) { this->anchorPoint_ = anchorPoint; }

	void SetIsFlipX(const bool& isFlipX) { this->isFlipX = isFlipX; }

	void SetIsFlipY(const bool& isFlipY) { this->isFlipY = isFlipY; }

	void SetIsInvisible(const bool& isInvisible) { this->isInvisible_ = isInvisible; }

private:

	SpriteCommon* spriteCommon_ = nullptr;

	XMFLOAT4 color = { 1,0,0,0.5f };

	float rotationZ;
	XMFLOAT2 position_;

	XMFLOAT2 size_ = { 200.0f,200.0f };

	XMFLOAT2 anchorPoint_ = { 0.0f,0.0f };

	bool isFlipX = false;
	bool isFlipY = false;

	bool isInvisible_ = false;

	Vertex vertices[4];


	//ワールド変換行列
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

