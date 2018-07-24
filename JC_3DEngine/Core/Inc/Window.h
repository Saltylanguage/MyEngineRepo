#pragma once

//Description: Class for Win32 Application window

namespace Core
{
	class Window
	{
	public:
		Window();
		~Window();

		void Initialize(HINSTANCE instance, LPCSTR appName, int width, int height);
		void Terminate();

		bool ProcessMessage();

		HWND GetWindowHandle() const { return mWindow; }

	private:
		HINSTANCE mInstance;
		HWND mWindow;

		std::string mAppName;
	};
} //namespace Core

