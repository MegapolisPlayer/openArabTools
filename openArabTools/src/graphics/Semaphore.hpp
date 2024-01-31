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

		Semaphore(SemaphoreOrientation aOrientation) noexcept;

		void setTitle(const std::string& aTitle);

		void showWindow();
		void hideWindow();

		void setRedOn();
		void setYellowOn();
		void setGreenOn();

		void setRedOff();
		void setYellowOff();
		void setGreenOff();

		void setRedOnOff();
		void setYellowOnOff();
		void setGreenOnOff();

		std::string getTitle();
		bool isRedOn();
		bool isYellowOn();
		bool isGreenOn();


		~Semaphore() noexcept;
	private:
		
	};
}