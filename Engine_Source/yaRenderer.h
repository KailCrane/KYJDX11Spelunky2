#pragma once

#include "CommonInclude.h"
#include "yaMath.h"
#include "yaGraphicsDevice11.h"

using namespace ya::math;
using namespace ya::graphics;

namespace ya::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVS;
	
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePS;

	void Initialize();
	void Release();
}

