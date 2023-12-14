#pragma once
#include "StandardInclude.hpp"

namespace OpenArabTools {
	namespace Utils {
		//Returns the OpenArabTools version (and the version of ArabTools it was based on) as a string literal
		OPENARABTOOLS_OBJ const char* Version() noexcept;

		//Sleeps on this thread, returns true for compatibility with ArabTools
		OPENARABTOOLS_OBJ bool Sleep(const U64 aMs) noexcept;

		//Returns if the string is empty (overload for C strings)
		OPENARABTOOLS_OBJ bool IsEmpty(const char* aString) noexcept;
		//Returns if the string is empty (overload for C++ strings)
		OPENARABTOOLS_OBJ bool IsEmpty(const std::string& aString) noexcept;
	
		//Returns string if not empty, otherwise returns nullptr (overload for C strings)
		OPENARABTOOLS_OBJ const char* NonEmpty(const char* aString) noexcept;
		//Returns string if not empty, otherwise returns nullptr (overload for C++ strings)
		OPENARABTOOLS_OBJ const std::string* NonEmpty(const std::string* const aString) noexcept;

		//Runs function in [aFunction] on multiple threads [aCount] times, returns immediately or if aWaitReturn is set after the functions complete the tasks
		OPENARABTOOLS_OBJ void RunConcurrently(const U64 aCount, const bool aWaitReturn, RunConcurrentlyCallback aFunction) noexcept;
	}
}