#pragma once
#include "Error.hpp"

namespace OpenArabTools {
	//Returns the OpenArabTools version (and the version of ArabTools it was based on) as a string literal
	OPENARABTOOLS_OBJ constexpr const char* Version() noexcept;

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

	class OPENARABTOOLS_OBJ ScopedTimer {
	public:
		ScopedTimer(const char* aName) noexcept;
		~ScopedTimer() noexcept;
	private:
		const char* mName;
		std::chrono::system_clock::time_point mStart;
	};
}