#pragma once
#include "Matrix.hpp"

namespace OpenArabTools {
	//ArabTools Semaphore orientation
	enum struct SemaphoreOrientation : uint8_t {
		NORMAL, UPSIDEUP = NORMAL, 
		UPSIDEDOWN, UPSIDELEFT, UPSIDERIGHT
	};

	//ArabTools Semaphore implementation
	class OPENARABTOOLS_OBJ Semaphore {
	public:
		//Constructor, creates normal semaphore
		Semaphore() noexcept;
		//Constructor, creates semaphore with orientation
		Semaphore(SemaphoreOrientation aOrientation) noexcept;

		void showWindow() noexcept;
		void hideWindow() noexcept;

		void setRedOn() noexcept;
		void setYellowOn() noexcept;
		void setGreenOn() noexcept;

		void setRedOff() noexcept;
		void setYellowOff() noexcept;
		void setGreenOff() noexcept;

		void setRedOnOff(const bool aOnOff) noexcept;
		void setYellowOnOff(const bool aOnOff) noexcept;
		void setGreenOnOff(const bool aOnOff) noexcept;

		std::string getTitle() const noexcept;
		bool isRedOn() const noexcept;
		bool isYellowOn() const noexcept;
		bool isGreenOn() const noexcept;

		//
		// OpenArabTools extensions
		//

		void toggleRed() noexcept;
		void toggleYellow() noexcept;
		void toggleGreen() noexcept;

		bool open() const noexcept;
		bool update() noexcept;
		void run() noexcept;

		void setTitle(const std::string& aTitle) noexcept;

		void showWindowAndRun() noexcept;
		bool sleep(const uint64_t aMs) noexcept;

		~Semaphore() noexcept;
	private:
		Matrix mMatrix;
		bool mIsFlipped;
		bool mIsRedOn, mIsYellowOn, mIsGreenOn;
	};
}