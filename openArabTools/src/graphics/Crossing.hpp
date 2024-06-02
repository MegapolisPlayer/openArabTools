#pragma once
#include "Semaphore.hpp"

namespace OpenArabTools {
	class OPENARABTOOLS_OBJ CrossingSemaphore {
	public:
		CrossingSemaphore() noexcept;



		~CrossingSemaphore() noexcept;
	private:

	};

	class OPENARABTOOLS_OBJ Crossing {
	public:
		Crossing() noexcept;

		void showWindow() noexcept;
		void hideWindow() noexcept;

		CrossingSemaphore& getSemaphoreA() noexcept;
		CrossingSemaphore& getSemaphoreB() noexcept;
		CrossingSemaphore& getSemaphoreC() noexcept;
		CrossingSemaphore& getSemaphoreD() noexcept;

		//
		// OpenArabTools necessities
		//

		bool open() const noexcept;
		bool update() noexcept;
		void run() noexcept;

		//
		// OpenArabTools extensions
		//

		void showWindowAndRun() noexcept;
		bool sleep(const U64 aMs) noexcept;

		~Crossing() noexcept;
	private:
		Internal::GLWindow mWindow;

	};
}