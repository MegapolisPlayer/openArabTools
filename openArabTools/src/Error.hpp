#pragma once
#include "StandardInclude.hpp"

namespace OpenArabTools {
	namespace Error {
		//NOTE: all strings must be NULL TERMINATED

		//"The Terminator" - shuts the program down
		[[noreturn]] void stop() noexcept;

		//Prints error and terminates program
		[[noreturn]] void error(const char* aMessage) noexcept;

		//Prints OpenGL error and terminates program
		[[noreturn]] void error(const char* aMessage, const char* aGLBuffer) noexcept;

		//Checks if library initialized, if not throws error
		bool noiniterror() noexcept;

		//Prints warning about something not library-breaking, but still incorrect
		void warning(const char* aMessage) noexcept;
	} //namespace Error
}