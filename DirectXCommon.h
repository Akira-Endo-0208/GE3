#pragma once

#include<wrl.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include <cassert>
#include<vector>
#include "WinApp.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

//DirectX基盤
class DirectXCommon
{
public:	//メンバ関数

	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	ID3D12Device* GetDevice() const { return device_.Get(); }

	ID3D12GraphicsCommandList* GetCommandList() const { return commandList_.Get(); }
	void Initialize(WinApp* winApp);

	void PreDraw();

	void PostDraw();
private: //初期化関数

	void InitializeDevice();

	void InitializeCommand();

	void InitializeSwapChain();

	void InitializeRenderTargetView();

	void InitializeDepthBuffer();

	void InitializeFence();

private: //メンバ変数

	HRESULT result_;
	ComPtr<IDXGIFactory7> dxgiFactory_;
	ComPtr<ID3D12Device> device_;
	ComPtr<IDXGISwapChain4> swapChain_;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
	ComPtr<ID3D12CommandAllocator> cmdAllocator_;
	ComPtr<ID3D12GraphicsCommandList> commandList_;
	ComPtr<ID3D12CommandQueue> commandQueue_;
	ComPtr<ID3D12DescriptorHeap> rtvHeap_;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc_{};
	//バックバッファ
	std::vector<ComPtr<ID3D12Resource>> backBuffers_;
	ComPtr<ID3D12Resource> depthBuff_;
	ComPtr <ID3D12DescriptorHeap> dsvHeap_;
	ComPtr<ID3D12Fence> fence_;
	UINT64 fenceVal = 0;

	D3D12_RESOURCE_BARRIER barrierDesc_{};
	//WindowsAPI
	WinApp* winApp_ = nullptr;
};

