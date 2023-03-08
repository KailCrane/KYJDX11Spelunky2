#pragma once

#include "yaGraphics.h"



namespace ya::graphics
{
	class GraphicsDevice11
	{
	public:
		GraphicsDevice11(ValidationMode validattionMode = ValidationMode::Disabled);
		~GraphicsDevice11();

		bool CreateSwapChain(DXGI_SWAP_CHAIN_DESC* desc);
		bool CreateTexture(D3D11_TEXTURE2D_DESC* desc, ID3D11Texture2D** ppTexture2D);
	
		bool CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buffer);
		bool CreateShader();

		void Draw();


	private:

		//Gpu 객체 생성, 그래픽 카드랑 연결되는 기본적인 객체 
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;  
		// Gpu 읽기 쓰기 //핸들 처럼 디바이스에 직접 접근하지 않고 받아와서 사용
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		
		//최종적으로 그려지는 도화지;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView; //뷰가 타겟에 접근하여 연산하는 식

		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;


		// 화면에 최종적으로 그려지는 백버퍼 (Freame Buffer)를 관리하고, 실제로 화면에 렌더링 하는 
		// 당담하는 객체이다.
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;


		//텍스쳐 로딩할 때 사용 
		ID3D11SamplerState* mSampler[];
	};

	inline GraphicsDevice11*& GetDevice()
	{
		static GraphicsDevice11* device = nullptr;
		return device;
	}
} 
