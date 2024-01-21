#pragma once
#include "../StandardInclude.hpp"

namespace OpenArabTools {
	namespace Internal {
		enum struct ErrorCode {   

		};

		void LogInfo();

		void LogWarning();

		void LogError();

		[[noreturn]] void Terminate();

		//TODO: implement these functions, add ScopedTimer and FPSCounter (inherits from ScopedTimer, just extra FPS calculation)
	}
}