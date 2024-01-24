#pragma once
#include "Matrix.hpp"

namespace OpenArabTools {
	//ArabTools Semaphore orientation
	enum struct SemaphoreOrientation : U08 {
		NORMAL, UPSIDEUP = NORMAL, 
		UPSIDEDOWN, UPSIDELEFT, UPSIDERIGHT
	};

	//ArabTools Semaphore implementation
	class OPENARABTOOLS_OBJ Semaphore {
	public:
		Semaphore() noexcept;

		std::string getTitle();

		void showWindow();

		void hideWindow();

		bool isRedOn();
		bool isYellowOn();
		bool isGreenOn();

		~Semaphore() noexcept;
	private:
		
	};
}