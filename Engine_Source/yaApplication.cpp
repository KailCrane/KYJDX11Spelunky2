#include "yaApplication.h"
#include "yaRenderer.h"

namespace ya
{
	using namespace graphics;

	Application::Application()
	{

	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}
	void Application::Initialize()
	{
		renderer::Initialize();

	}
	void Application::Update()
	{
	}
	void Application::FixedUpdate()
	{
	}
	void Application::Render()
	{
		graphicDevice->Draw();
	}
	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;
		
			ValidationMode vailidationMode = ValidationMode::Disabled;
			graphicDevice = std::make_unique<GraphicsDevice11>();
			graphics::GetDevice() = graphicDevice.get();
		}

	}
}
