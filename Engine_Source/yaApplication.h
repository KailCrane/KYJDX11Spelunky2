#pragma once

#include "yaGraphicsDevice11.h"
#include"yaApplication.h"
#include "yaEngine.h"
#include "yaGraphics.h"
#include "CommonInclude.h"

namespace ya
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		virtual void Initialize();

		// ���� �����̶���� �̵��̶����
		// Cpu ������ ���ư��� ��
		virtual void Update();

		//Gpu ������Ʈ
		virtual void FixedUpdate();

		virtual void Render();

		void SetWindow(HWND hwnd, UINT width, UINT height);

		void SetHwnd(HWND hwnd) { mHwnd = hwnd; }
		HWND GetHwnd() { return mHwnd; }
		UINT GetHeight() { return mHeight; }
		UINT GetWidth() { return mWidth; }

	private:
		bool initialized = false;
		std::unique_ptr<graphics::GraphicsDevice11> graphicDevice;
		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;
	};
}