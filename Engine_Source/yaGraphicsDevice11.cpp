#include "yaGraphicsDevice11.h"
#include "yaApplication.h"
#include "yaRenderer.h"
extern ya::Application application;

namespace ya::graphics
{
	GraphicsDevice11::GraphicsDevice11(ValidationMode validationMode)
	{
		HWND hwnd = application.GetHwnd();

		//Device, Device Context 디바이스를 여러게 만들 수 있으나 보통 게임에서는 안 그런다고 한다
		UINT DeviceFlag = D3D11_CREATE_DEVICE_DEBUG; //여러개 있으나 DEBUG로 만들어야 디버그 됨
		D3D_FEATURE_LEVEL FeatureLevel = (D3D_FEATURE_LEVEL)0;

		//ID3D11Device* pDevice = nullptr;
	
		HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
			, DeviceFlag, nullptr, 0
			, D3D11_SDK_VERSION
			, mDevice.GetAddressOf()
			, &FeatureLevel
			, mContext.GetAddressOf());

		//SwapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 144;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		if (!CreateSwapChain(&swapChainDesc))
		{
			return;
		}

		//spawnchain을 위한 rendertarger
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf());

		//rendertargetview 만들기

		hr = mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

		D3D11_TEXTURE2D_DESC deapthBuffer = {};
		deapthBuffer.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		deapthBuffer.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		deapthBuffer.Usage = D3D11_USAGE_DEFAULT;
		deapthBuffer.CPUAccessFlags = 0;
		deapthBuffer.Width = application.GetWidth();
		deapthBuffer.Height = application.GetHeight();
		deapthBuffer.ArraySize = 1;
		deapthBuffer.SampleDesc.Count = 1;
		deapthBuffer.SampleDesc.Quality = 0;
		deapthBuffer.MiscFlags = 0;
	
		if (!CreateTexture(&deapthBuffer, mDepthStencilBuffer.GetAddressOf()));
		{
			return;
		}
		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.ReleaseAndGetAddressOf())))
		{
			return;
		}
	}

	GraphicsDevice11::~GraphicsDevice11()
	{

	}
	bool GraphicsDevice11::CreateSwapChain(DXGI_SWAP_CHAIN_DESC* desc)
	{ 
		Microsoft::WRL::ComPtr<IDXGIDevice>  pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter>  pDXGIAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory>  pDXGIFactory = nullptr;


		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
		{
			return false;
		}
		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdapter.GetAddressOf())))
		{
			return false;
		}
		if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pDXGIFactory.GetAddressOf())))
		{
			return false;
		}
		if (FAILED(pDXGIFactory->CreateSwapChain(mDevice.Get(),desc,mSwapChain.GetAddressOf())))
		{
			return false;
		}
		return true;
	}
	bool GraphicsDevice11::CreateTexture(D3D11_TEXTURE2D_DESC* desc, ID3D11Texture2D** ppTexture2D)
	{
		if (FAILED(mDevice->CreateTexture2D(desc, nullptr, ppTexture2D)))
		{
			return false;
		}
		return true;
	}
	bool GraphicsDevice11::CreateBuffer(D3D11_BUFFER_DESC* desc,  D3D11_SUBRESOURCE_DATA* data ,ID3D11Buffer** buffer)
	{
		if (FAILED(mDevice->CreateBuffer(desc, data, buffer)))
		{
			return false;
		}

		return true;
	}
	bool GraphicsDevice11::CreateShader()
	{
		ID3DBlob* errorBlob = nullptr;

		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += "\\SHADER_SOURCE\\";

		std::wstring vsPath(shaderPath.c_str());
		vsPath += L"TriangleVS.hlsl"; 
		D3DCompileFromFile(vsPath.c_str(),nullptr,D3D_COMPILE_STANDARD_FILE_INCLUDE
							, "VS_TEST","vs_5_0",0,0,&renderer::triangleVSBlob,&errorBlob);

		mDevice->CreateVertexShader(renderer::triangleVSBlob->GetBufferPointer(), 
										renderer::triangleVSBlob->GetBufferSize()
										, nullptr, &renderer::triangleVS);


		std::wstring psPath(shaderPath.c_str());
		psPath += L"TriangleVS.hlsl";
		D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "PS_TEST", "ps_5_0", 0, 0, &renderer::trianglePSBlob, &errorBlob);

		mDevice->CreatePixelShader(renderer::trianglePSBlob->GetBufferPointer(),
			renderer::trianglePSBlob->GetBufferSize()
			, nullptr, &renderer::trianglePS);



		return true;
	}
	void GraphicsDevice11::Draw()
	{
		FLOAT backgroundColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), backgroundColor);

		mSwapChain->Present(1,0);

	}
}


