#include "yaRenderer.h"
#include "yaGraphicsDevice11.h"

using namespace ya::graphics;
 
namespace ya::renderer
{
	Vertex vertexes[3] = {};

	ID3D11Buffer* triangleBuffer = nullptr;
	ID3DBlob* errorBlob = nullptr;

	ID3DBlob* triangleVSBlob = nullptr;
	ID3D11VertexShader* triangleVS = nullptr;

	ID3DBlob* trianglePSBlob = nullptr;
	ID3D11PixelShader* trianglePS = nullptr;

	ID3D11InputLayout* triangleLayout = nullptr;

	void SetUpState()
	{
		

	}

	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = {};

		triangleDesc.ByteWidth = sizeof(Vertex) * 3;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;

		GetDevice()->CreateBuffer(&triangleDesc,&triangleData, &triangleBuffer);
	}

	void LoadShader()
	{
		GetDevice()->CreateShader();
	}


	void Initialize()
	{
		vertexes[0].pos = Vector3(0.0f, 0.5f, 1.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f,1.0f);

		vertexes[1].pos = Vector3(-0.5f, -0.5f, 1.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f,1.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 1.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f,1.0f);

		SetUpState();
		LoadBuffer();
		LoadShader();

	}

	void Release()
	{

	}
}