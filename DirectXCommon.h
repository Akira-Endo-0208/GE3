#pragma once

#include<wrl.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include <cassert>
#include<vector>
#include "WinApp.h"
//DirectX基盤
class DirectXCommon
{
public:	//メンバ関数

	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	ComPtr<ID3D12Device> GetDevice() const { return device; }
	//初期化
	void Initialize();

private:
	HRESULT result;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12Device> device;
	ComPtr<IDXGISwapChain4> swapChain;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	//WindowsAPI
	WinApp* winApp_ = nullptr;
};

