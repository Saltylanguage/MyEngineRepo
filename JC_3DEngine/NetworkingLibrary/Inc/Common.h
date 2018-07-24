#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

#pragma comment(lib, "Ws2_32.lib")

#include <Core\Inc\Core.h>

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <mutex>
#include <unordered_map>
#include <string>
#include <thread>
#include <vector>

//template <typename T>
//inline void SafeDelete(T*& ptr)
//{
//	delete ptr;
//	ptr = nullptr;
//}
//
//template <typename T>
//inline void SafeDeleteArray(T*& ptr)
//{
//	delete[] ptr;
//	ptr = nullptr;
//}