#pragma once
#include "debug/Debug.hpp"

namespace OpenArabTools {
	extern S64 gsInit; //Amount of initializations

	//Gets if library initialized
	OPENARABTOOLS_OBJ bool isLibInit() noexcept;

	//Initializes the library
	OPENARABTOOLS_OBJ void init() noexcept;

	//Terminates the library
	OPENARABTOOLS_OBJ void terminate() noexcept;

	//Returns the OpenArabTools version (and the version of ArabTools it was based on) as a string literal
	OPENARABTOOLS_OBJ const char* Version() noexcept;

	//Returns the OpenArabTools build ID
	OPENARABTOOLS_OBJ constexpr U64 buildID() noexcept;

	namespace Utils {
		//Sleeps on this thread, returns true for compatibility with ArabTools
		OPENARABTOOLS_OBJ bool sleep(const U64 aMs) noexcept;

		//NOTE: C style strings must be null terminated.

		//Returns if the string is empty (overload for C strings)
		OPENARABTOOLS_OBJ bool isEmpty(const char* aString) noexcept;
		//Returns if the string is empty (overload for C++ strings)
		OPENARABTOOLS_OBJ bool isEmpty(const std::string& aString) noexcept;
	
		//Returns string if not empty, otherwise returns nullptr (overload for C strings)
		OPENARABTOOLS_OBJ const char* const nonEmpty(const char* aString) noexcept;
		//Returns string if not empty, otherwise returns nullptr (overload for C++ strings)
		OPENARABTOOLS_OBJ const std::string* nonEmpty(const std::string* const aString) noexcept;

		//Runs function in [aFunction] on multiple threads [aCount] times, returns immediately or if aWaitReturn is set after the functions complete the tasks
		//NOTE: returns immediately if another instance is already running, lambdas also possible
		OPENARABTOOLS_OBJ void runConcurrently(const U64 aCount, const bool aWaitReturn, RunConcurrentlyCallback aFunction) noexcept;
	}
}