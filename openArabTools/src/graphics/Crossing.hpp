#pragma once
#include "Semaphore.hpp"

namespace OpenArabTools {
	constexpr U64 SEMAPHOREID_A = 0;
	constexpr U64 SEMAPHOREID_B = 1;
	constexpr U64 SEMAPHOREID_C = 2;
	constexpr U64 SEMAPHOREID_D = 3;

	class OPENARABTOOLS_OBJ CrossingSemaphoreAccessor {
	public:
		friend class Crossing;

		//When called manually creates an object not bound by the automatic destruction on Crossing close - Use at your own risk!
		CrossingSemaphoreAccessor(Crossing* aParent, const U64 aSemaphoreId) noexcept;

		CrossingSemaphoreAccessor() = delete;
		CrossingSemaphoreAccessor(const CrossingSemaphoreAccessor& aOther) = delete;
		CrossingSemaphoreAccessor(CrossingSemaphoreAccessor&& aOther) = delete;

		void setRedOn() noexcept;
		void setYellowOn() noexcept;
		void setGreenOn() noexcept;

		void setRedOff() noexcept;
		void setYellowOff() noexcept;
		void setGreenOff() noexcept;

		void setRedOnOff(const bool aOnOff) noexcept;
		void setYellowOnOff(const bool aOnOff) noexcept;
		void setGreenOnOff(const bool aOnOff) noexcept;

		bool isRedOn() const noexcept;
		bool isYellowOn() const noexcept;
		bool isGreenOn() const noexcept;

		void toggleRed() noexcept;
		void toggleYellow() noexcept;
		void toggleGreen() noexcept;

		~CrossingSemaphoreAccessor() noexcept;
	private:
		Crossing* mParent;
		U64 mSemaphoreId;
	};

	class OPENARABTOOLS_OBJ Crossing {
	public:
		friend class CrossingSemaphoreAccessor;

		Crossing() noexcept;
		Crossing(const std::string& aFilename) noexcept;

		void showWindow() noexcept;
		void hideWindow() noexcept;

		std::weak_ptr<CrossingSemaphoreAccessor> getSemaphore(const U64 aId) noexcept;

		void showSemaphore(const U64 aId) noexcept;
		void hideSemaphore(const U64 aId) noexcept;

		//
		// OpenArabTools necessities
		//

		bool open() const noexcept;
		bool update() noexcept;
		void run() noexcept;

		//
		// OpenArabTools extensions
		//

		void setTitle(const std::string& aTitle) noexcept;

		void showWindowAndRun() noexcept;
		bool sleep(const U64 aMs) noexcept;

		~Crossing() noexcept;
	private:
		Matrix mMatrix;

		U64 getQuadrantId(const U64 aX, const U64 aY) noexcept;
		void drawFromString(const std::string& aString) noexcept;

		//Semaphore 0: Exists, Red, Yellow, Green
		//Semaphore 1: Exists, Red, Yellow, Green
		//Semaphore 2: Exists, Red, Yellow, Green
		//Semaphore 3: Exists, Red, Yellow, Green
		std::array<bool, 16> mSemaphoreStates;

		//Diagram of window:
		//   R   R = Road
		//  0R1
		//RRRRRRR
		//  2R3
		//   R

		std::vector<std::shared_ptr<CrossingSemaphoreAccessor>> mAccessors;
	};
}