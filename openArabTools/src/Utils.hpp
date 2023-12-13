#pragma once
#include "StandardInclude.hpp"

namespace OpenArabTools {
	namespace Utils {
		//Returns the OpenArabTools version as a string literal
		OPENARABTOOLS_OBJ const char* Version() noexcept;

		//Sleeps on this thread
		OPENARABTOOLS_OBJ void Sleep(U64 aMs) noexcept;
	}
}