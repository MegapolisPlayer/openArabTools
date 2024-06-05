#pragma once
#include "Error.hpp"

namespace OpenArabTools {
	//Returns the OpenArabTools version (and the version of ArabTools it was based on) as a string literal
	OPENARABTOOLS_OBJ constexpr const char* Version() noexcept;

	//Returns the OpenArabTools build ID
	OPENARABTOOLS_OBJ constexpr uint64_t buildID() noexcept;

	namespace Utils {
		//Sleeps on this thread, returns true for compatibility with ArabTools
		OPENARABTOOLS_OBJ bool sleep(const uint64_t aMs) noexcept;

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
		OPENARABTOOLS_OBJ void runConcurrently(const uint64_t aCount, const bool aWaitReturn, RunConcurrentlyCallback aFunction) noexcept;

		//(Extension) Just gets a bool, 50% false, 50% true
		OPENARABTOOLS_OBJ bool getRandomBool() noexcept;
	}

	//Class for measuring time of a scope. Just create it in the scope to be measured
	class OPENARABTOOLS_OBJ ScopedTimer {
	public:
		//Starts the timer
		ScopedTimer(const char* aName) noexcept;
		//Stops the timer
		~ScopedTimer() noexcept;
	private:
		const char* mName;
		std::chrono::system_clock::time_point mStart;
	};
}