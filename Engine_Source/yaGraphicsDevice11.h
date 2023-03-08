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

		//Gpu ��ü ����, �׷��� ī��� ����Ǵ� �⺻���� ��ü 
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;  
		// Gpu �б� ���� //�ڵ� ó�� ����̽��� ���� �������� �ʰ� �޾ƿͼ� ���
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		
		//���������� �׷����� ��ȭ��;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView; //�䰡 Ÿ�ٿ� �����Ͽ� �����ϴ� ��

		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;


		// ȭ�鿡 ���������� �׷����� ����� (Freame Buffer)�� �����ϰ�, ������ ȭ�鿡 ������ �ϴ� 
		// ����ϴ� ��ü�̴�.
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;


		//�ؽ��� �ε��� �� ��� 
		ID3D11SamplerState* mSampler[];
	};

	inline GraphicsDevice11*& GetDevice()
	{
		static GraphicsDevice11* device = nullptr;
		return device;
	}
} 
