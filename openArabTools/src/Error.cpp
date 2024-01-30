#include "Error.hpp"

namespace OpenArabTools {
	namespace Error {
		[[noreturn]] void stop() noexcept {
			Internal::InitAmount = 1; //override so terminate() actually terminates
			terminate();
		}

		[[noreturn]] void error(const char* aMessage) noexcept {
			std::cout << "openArabTools: ERROR: " << aMessage << "\n";
			stop();
		}

		[[noreturn]] void error(const char* aMessage, const char* aGLBuffer) noexcept {
			std::cout << "openArabTools: ERROR: " << aMessage << ": " << aGLBuffer << "\n";
			stop();
		}

		void warning(const char* aMessage) noexcept {
			std::cout << "openArabTools: WARNING: " << aMessage << "\n";
		}
	}
}