#pragma once

//Description: Application base class.

#include "NonCopyable.h"

namespace Core
{
	class Application
	{
		NONCOPYABLE(Application);

	public:

		Application();
		virtual ~Application();

		void Initialize(HINSTANCE instance, LPCSTR appName, uint32_t width, uint32_t height);
		void Terminate();

		void HookWindow(HWND hWnd);
		void UnhookWindow();

		void Update();

		void Kill(){ mRunning = false; }
		HINSTANCE GetInstance() const { return mInstance; }
		HWND GetWindow() const { return mWindow; }
		const char* GetAppName() const { return mAppName.c_str();}
		bool IsRunning() const { return mRunning; }

	private:
		virtual void OnInitialize(uint32_t width, uint32_t height) = 0;
		virtual void OnTerminate() = 0;
		virtual void OnUpdate() = 0;

	private:

		HINSTANCE mInstance;
		HWND mWindow;
		std::string mAppName;
		bool mRunning;

	};
}	//namespace core

//Const correctness
//Bitwise constness
//conceptual constness
//
//class Container
//{
//public: 
//	
//	void Start() {nextItem = 0;}
//	int GetNext() const { stuff[nextItem++];}
//
//
//private:
//	
//	std::vector<int> stuff;
//	mutable int nextItem;
//
//};
//
////void DoStuff(Foo foo) // pass by value
////void DoStuff(Foo& foo) //pass by reference
//void DoStuff(const Container& foo) // pass by const reference
//{
//	//do stuff with foo
//}


//stack frame
// has 3 things:
// 1) local variables
// 2) parameters
// 3) return address