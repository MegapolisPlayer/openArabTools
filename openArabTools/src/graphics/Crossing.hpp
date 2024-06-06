#pragma once
#include "Semaphore.hpp"

namespace OpenArabTools {
	constexpr uint64_t SEMAPHOREID_A = 0;
	constexpr uint64_t SEMAPHOREID_B = 1;
	constexpr uint64_t SEMAPHOREID_C = 2;
	constexpr uint64_t SEMAPHOREID_D = 3;

	//Accessor for semaphores drawn on Crossing.
	class OPENARABTOOLS_OBJ CrossingSemaphoreAccessor {
	public:
		friend class Crossing;

		//When called manually creates an object not bound by the automatic destruction on Crossing close - Use at your own risk!
		CrossingSemaphoreAccessor(Crossing* aParent, const uint64_t aSemaphoreId) noexcept;

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
		uint64_t mSemaphoreId;
	};

	//Accessor for semaphores drawn on Crossing.
	using CSemaphore = CrossingSemaphoreAccessor;

	//Diagram of crossing window:
	//   |
	//  0|1
	//---+---
	//  2|3
	//   |
		
	//Class showcasing a simple crossing with multiple independent semaphores
	class OPENARABTOOLS_OBJ Crossing {
	public:
		friend class CrossingSemaphoreAccessor;

		Crossing() noexcept;
		Crossing(const std::string& aFilename) noexcept;

		void showWindow() noexcept;
		void hideWindow() noexcept;

		//Returns a pointer to the accessor.
		CrossingSemaphoreAccessor* const getSemaphore(const uint64_t aId) noexcept;

		void showSemaphore(const uint64_t aId) noexcept;
		void hideSemaphore(const uint64_t aId) noexcept;

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
		bool sleep(const uint64_t aMs) noexcept;

		~Crossing() noexcept;
	private:
		Matrix mMatrix;

		uint64_t getQuadrantId(const uint64_t aId) noexcept;

		void validateString(const std::string& aString) noexcept;
		void drawFromString(const std::string& aString) noexcept;

		//Semaphore info
		struct SemaphoreInfo {
			uint64_t RedX = 0, RedY = 0;
			uint64_t YellowX = 0, YellowY = 0;
			uint64_t GreenX = 0, GreenY = 0;
			bool Hidden = true;
		};
		std::array<SemaphoreInfo, 4> mSemaphoreInfo;

		std::vector<CrossingSemaphoreAccessor*> mAccessors;
	};
}