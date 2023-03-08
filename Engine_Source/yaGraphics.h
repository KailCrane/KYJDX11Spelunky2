#pragma once
//#include "CommonInclude.h"
#include "yaMath.h"
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
namespace ya::graphics
{
	enum class ValidationMode
	{
		Disabled,
		Enabled,
		Gpu,
	};

	enum class eShaderStage
	{
		VS,
		PS,
		Count,
	};

	/*struct SwapChin
	{
	};*/


}