#include "Error.hpp"

namespace OpenArabTools {
	namespace Error {
		[[noreturn]] void stop() noexcept {
			Internal::IsInit = 1; //override so terminate() actually terminates
			terminate();
		}

		[[noreturn]] void error(const char* aMessage) noexcept {
			std::cerr << "openArabTools: ERROR: " << aMessage << "\n";
			stop();
		}

		[[noreturn]] void error(const char* aMessage, const char* aGLBuffer) noexcept {
			std::cerr << "openArabTools: ERROR: " << aMessage << ": " << aGLBuffer << "\n";
			stop();
		}
		
		bool noiniterror() noexcept {
			if (isLibInit()) return false;
			std::cerr << "openArabTools: ERROR: Library not initialized.\n";
			stop();
			return true; 
		}

		void warning(const char* aMessage) noexcept {
			std::cerr << "openArabTools: WARNING: " << aMessage << "\n";
		}
	}
}