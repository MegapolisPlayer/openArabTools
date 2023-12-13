#pragma once
#ifndef OPENARABTOOLS_NO_STANDARD_INCLUDE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
#endif

#ifdef OPENARABTOOLS_BUILD_DLL
#define OPENARABTOOLS_OBJ _declspec(dllexport)
#else
#define OPENARABTOOLS_OBJ _declspec(dllimport)
#endif

#ifndef OPENARABTOOLS_NO_EXTENSIONS
#define OPENARABTOOLS_EXTENSION(x) x
#else
#define OPENARABTOOLS_EXTENSION(x) 
#endif

namespace OpenArabTools {
	//General declarations of shorthand fixed-width types

	typedef int8_t   S08;
	typedef int16_t  S16;
	typedef int32_t  S32;
	typedef int64_t  S64;
	typedef uint8_t  U08;
	typedef uint16_t U16;
	typedef uint32_t U32;
	typedef uint64_t U64;

	//Decimal number
	typedef long double Dec;

	//Callback for an interation with the Matrix class
	typedef bool(MatrixInteractionCallback)(const U64 aX, const U64 aY);
}