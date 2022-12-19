#pragma once
#include "SpriteCommon.h"
#include <DirectXMath.h>

using namespace DirectX;
using namespace Microsoft::WRL;

class Sprite
{
public:

	//èâä˙âª
	void Initialize(SpriteCommon* spriteCommon);

	void Draw();
private:
	SpriteCommon* spriteCommon_ = nullptr;

	ComPtr<ID3D12Resource> vertBuff;

	D3D12_VERTEX_BUFFER_VIEW vbView{};
};

