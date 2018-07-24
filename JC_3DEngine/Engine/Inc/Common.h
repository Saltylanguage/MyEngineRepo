#ifndef INCLUDED_ENGINE_COMMON_H
#define INCLUDED_ENGINE_COMMON_H

//====================================================================================================
// Filename:	Common.h
// Created by:	Peter Chan
// Description:	Header for common includes, typedefs, and helper functions.
//====================================================================================================

//====================================================================================================
// Defines
//====================================================================================================

#define DIRECTINPUT_VERSION 0x0800

//====================================================================================================
// Includes
//====================================================================================================

#include <Core\Inc\Core.h>
// Standard headers
#include <windowsx.h>

// STL headers
#include <list>
#include <map>
#include <string>
#include <vector>

// DirectX headers
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <dinput.h>
#include <DirectXMath.h>

using namespace DirectX;

//====================================================================================================
// Typedefs
//====================================================================================================

typedef char				s8;
typedef short				s16;
typedef int					s32;
typedef __int64				s64;

typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned __int64	u64;

typedef float				f32;
typedef double				f64;

//====================================================================================================
// Limits
//====================================================================================================

#define U8_MAX				(u8)-1
#define U16_MAX				(u16)-1
#define U32_MAX				(u32)-1
#define U64_MAX				(u64)-1

#define F32_MIN				FLT_MIN
#define F32_MAX				FLT_MAX

#endif // #ifndef INCLUDED_ENGINE_COMMON_H