#pragma once

#include<wrl.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include <cassert>
#include<vector>
#include "WinApp.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

//DirectX���
class DirectXCommon
{
public:	//�����o�֐�

	//namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	ComPtr<ID3D12Device> GetDevice() const { return device_; }

	void Initialize(WinApp* winApp);

private: //�������֐�

	void InitializeDevice();

	void InitializeCommand();

	void InitializeSwapChain();

	void InitializeRenderTargetView();

	void InitializeDepthBuffer();

	void InitializeFence();

private: //�����o�ϐ�

	HRESULT result_;
	ComPtr<IDXGIFactory7> dxgiFactory_;
	ComPtr<ID3D12Device> device_;
	ComPtr<IDXGISwapChain4> swapChain_;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
	ComPtr<ID3D12CommandAllocator> cmdAllocator_;
	ComPtr<ID3D12GraphicsCommandList> commandList_;
	ComPtr<ID3D12CommandQueue> commandQueue_;
	ComPtr<ID3D12DescriptorHeap> rtvHeap_;
	//�o�b�N�o�b�t�@
	std::vector<ComPtr<ID3D12Resource>> backBuffers_;
	ComPtr<ID3D12Resource> depthBuff_;
	ComPtr<ID3D12Fence> fence_;
	//WindowsAPI
	WinApp* winApp_ = nullptr;
};

