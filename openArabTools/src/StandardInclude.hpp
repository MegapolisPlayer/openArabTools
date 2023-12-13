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

