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
		//Constructor, creates normal semaphore
		Semaphore() noexcept;

		Semaphore(SemaphoreOrientation aOrientation) noexcept;

		void setTitle(const std::string& aTitle) noexcept;

		void showWindow() noexcept;
		void hideWindow() noexcept;

		void setRedOn() noexcept;
		void setYellowOn() noexcept;
		void setGreenOn() noexcept;

		void setRedOff() noexcept;
		void setYellowOff() noexcept;
		void setGreenOff() noexcept;

		void setRedOnOff() noexcept;
		void setYellowOnOff() noexcept;
		void setGreenOnOff() noexcept;

		std::string getTitle() noexcept;
		bool isRedOn() noexcept;
		bool isYellowOn() noexcept;
		bool isGreenOn() noexcept;

		// OPENARABTOOLS necessities

		//Returns if window is open
		bool open() const noexcept;

		//Call this in a loop, returns if window still open
		bool update() noexcept;

		//Call this once, blocks execution until window closed!
		void run() noexcept;

		~Semaphore() noexcept;
	private:
		Matrix mMatrix;
		bool mIsFlipped;
		bool mIsRedOn, mIsYellowOn, mIsGreenOn;
	};
}