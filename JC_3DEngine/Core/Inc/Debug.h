#pragma once

#if defined(_DEBUG)
#define LOG(format,...)\
{\
	char buffer[1024];\
	int ret = _snprintf_s(buffer, _countof(buffer), _TRUNCATE, (#format), __VA_ARGS__);\
	OutputDebugStringA(buffer);\
	if(ret == -1) OutputDebugStringA("** message truncated **\n");\
	OutputDebugStringA("\n");\
}

#define ASSERT(condition, format, ...)\
{\
	if(!(condition))\
	{\
		LOG(format,__VA_ARGS__)\
		DebugBreak();\
	}\
}

#define VERIFY(condition, format, ...)\
		ASSERT(condition, format, __VA_ARGS__)
	


#else
#define LOG(format,...)
#define ASSERT(condition,format,...)
#define VERIFY(condition, format, ...) condition;

#endif //#if defined(_DEBUG)

