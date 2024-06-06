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
#include <numeric>
#include <array>
#include <fstream>
#include <random>
#include <algorithm>
#endif

//Uncomment this line to include full debug information, used when building OAT
//#define OPENARABTOOLS_PRINT_DEBUG_INFO

#ifdef _WIN32

#ifdef OPENARABTOOLS_BUILD_DLL
#define OPENARABTOOLS_OBJ _declspec(dllexport)
#else
#define OPENARABTOOLS_OBJ _declspec(dllimport)
#endif

#else

#define OPENARABTOOLS_OBJ

#endif

namespace OpenArabTools {
	//Callback for a function called by RunConcurrently (params: No. of thread from 0 (main), Id of job, do not return)
	typedef void(RunConcurrentlyCallback)(const uint8_t, const uint64_t);

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

//Using declarations

using namespace std::chrono_literals;

//Utility macros

//Normalize 0-255 range to 0-1
#define NORMAL255(x) x/255.0
//Normalize 0-1023 range to 0-1
#define NORMAL1023(x) x/1023.0

// Jokes...

#define train auto