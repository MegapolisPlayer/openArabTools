#pragma once
#ifndef OPENARABTOOLS_NO_STANDARD_INCLUDE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#endif

#ifdef OPENARABTOOLS_BUILD_DLL
#define OPENARABTOOLS_OBJ _declspec(dllexport)
#else
#define OPENARABTOOLS_OBJ _declspec(dllimport)
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

	typedef U16 CallbackStatusType; //callback return code type
	constexpr CallbackStatusType SUCCESSCODE = 1; //callback success
	constexpr CallbackStatusType FAILURECODE = 0; //callback failure

	//Decimal number
	typedef long double Dec;

	//Callback for a function called by RunConcurrently (params: No. of thread from 0 (main), Id of job, do not return)
	typedef void(RunConcurrentlyCallback)(const U08, const U64);
	//Callback for an interaction with the Matrix class (params: X and Y of light, return SUCCESSCODE or FAILURECODE)
	typedef bool(MatrixInteractionCallback)(const U64, const U64);

	namespace Internal {
		//Amount of initializations
		extern bool IsInit;
	}

	//Gets if library initialized
	OPENARABTOOLS_OBJ bool isLibInit() noexcept;
	//Initializes the library
	OPENARABTOOLS_OBJ void init() noexcept;
	//Terminates the library
	OPENARABTOOLS_OBJ void terminate() noexcept;
}

//Utility macros

//Normalize 0-255 range to 0-1
#define NORMAL255(x) x/255.0
//Normalize 0-1023 range to 0-1
#define NORMAL1023(x) x/1023.0

// Jokes...

#define TRAIN auto