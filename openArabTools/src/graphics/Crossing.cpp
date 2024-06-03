#include "Crossing.hpp"

#define SEMAPHORE_ROW_SIZE 4
#define SEMAPHORE_RED_OFFSET 1
#define SEMAPHORE_YELLOW_OFFSET 2
#define SEMAPHORE_GREEN_OFFSET 3

namespace OpenArabTools {
	CrossingSemaphoreAccessor::CrossingSemaphoreAccessor(Crossing* aParent, const U64 aSemaphoreId) noexcept
	: mParent(nullptr), mSemaphoreId(INT64_MAX) {
		if (this->mSemaphoreId >= 4) { 
			Error::warning("Semaphore id out of range in accessor: delete this accessor. (This will cause a segmentation fault otherwise.)"); 
			return; 
		}
		this->mParent = aParent;
		this->mSemaphoreId = aSemaphoreId;
	}

	void CrossingSemaphoreAccessor::setRedOn() noexcept {
		this->setRedOnOff(true);
	}
	void CrossingSemaphoreAccessor::setYellowOn() noexcept {
		this->setYellowOnOff(true);
	}
	void CrossingSemaphoreAccessor::setGreenOn() noexcept {
		this->setGreenOnOff(true);
	}

	void CrossingSemaphoreAccessor::setRedOff() noexcept {
		this->setRedOnOff(false);
	}
	void CrossingSemaphoreAccessor::setYellowOff() noexcept {
		this->setYellowOnOff(false);
	}
	void CrossingSemaphoreAccessor::setGreenOff() noexcept {
		this->setGreenOnOff(false);
	}

	void CrossingSemaphoreAccessor::setRedOnOff(const bool aOnOff) noexcept {
		this->mParent->mSemaphoreStates[(this->mSemaphoreId * SEMAPHORE_ROW_SIZE) + SEMAPHORE_RED_OFFSET] = aOnOff;
	}
	void CrossingSemaphoreAccessor::setYellowOnOff(const bool aOnOff) noexcept {
		this->mParent->mSemaphoreStates[(this->mSemaphoreId * SEMAPHORE_ROW_SIZE) + SEMAPHORE_YELLOW_OFFSET] = aOnOff;
	}
	void CrossingSemaphoreAccessor::setGreenOnOff(const bool aOnOff) noexcept {
		this->mParent->mSemaphoreStates[(this->mSemaphoreId * SEMAPHORE_ROW_SIZE) + SEMAPHORE_GREEN_OFFSET] = aOnOff;
	}

	bool CrossingSemaphoreAccessor::isRedOn() const noexcept {
		return this->mParent->mSemaphoreStates[(this->mSemaphoreId * SEMAPHORE_ROW_SIZE) + SEMAPHORE_RED_OFFSET];
	}
	bool CrossingSemaphoreAccessor::isYellowOn() const noexcept {
		return this->mParent->mSemaphoreStates[(this->mSemaphoreId * SEMAPHORE_ROW_SIZE) + SEMAPHORE_YELLOW_OFFSET];
	}
	bool CrossingSemaphoreAccessor::isGreenOn() const noexcept {
		return this->mParent->mSemaphoreStates[(this->mSemaphoreId * SEMAPHORE_ROW_SIZE) + SEMAPHORE_GREEN_OFFSET];
	}

	void CrossingSemaphoreAccessor::toggleRed() noexcept {
		this->setRedOnOff(!this->isRedOn());
	}
	void CrossingSemaphoreAccessor::toggleYellow() noexcept {
		this->setYellowOnOff(!this->isYellowOn());
	}
	void CrossingSemaphoreAccessor::toggleGreen() noexcept {
		this->setGreenOnOff(!this->isGreenOn());
	}

	CrossingSemaphoreAccessor::~CrossingSemaphoreAccessor() noexcept {}

	Crossing::Crossing() noexcept {
		this->mMatrix.set(30, 30);
		this->mSemaphoreStates = { false };

		//Draw 4-way crossing using matrix background and foreground

		this->mMatrix.setBackground(LIGHTCOLOR_GREEN);

		//TODO: load from file in resource folder: 30x30 string

		//Draw road

		//Draw Semaphores
	}

	void Crossing::showWindow() noexcept {
		this->mMatrix.showWindow();
	}
	void Crossing::hideWindow() noexcept {
		this->mMatrix.hideWindow();
	}

	//shared pointer contained ONLY in the main crossing class

	std::weak_ptr<CrossingSemaphoreAccessor> Crossing::getSemaphore(const U64 aId) noexcept {
		if (aId >= 4) { Error::error("Semaphore ID out of range"); return {}; }
		this->mAccessors.push_back(std::make_shared<CrossingSemaphoreAccessor>(this, aId));
		return std::weak_ptr(this->mAccessors.back());
	}

	void showSemaphore(const U64 aId) noexcept {
		if (aId >= 4) { Error::error("Semaphore ID out of range"); return; }

		switch (aId) {

		}
	}
	void hideSemaphore(const U64 aId) noexcept {
		if (aId >= 4) { Error::error("Semaphore ID out of range"); return; }

		switch (aId) {

		}
	}

	bool Crossing::open() const noexcept {
		return this->mMatrix.open();
	}
	bool Crossing::update() noexcept {
		return this->mMatrix.update();
	}
	void Crossing::run() noexcept {
		this->mMatrix.run();
	}

	void Crossing::setTitle(const std::string& aTitle) noexcept {
		this->mMatrix.setTitle(aTitle);
	}

	void Crossing::showWindowAndRun() noexcept {
		this->mMatrix.showWindowAndRun();
	}
	bool Crossing::sleep(const U64 aMs) noexcept {
		return this->mMatrix.sleep(aMs);
	}

	Crossing::~Crossing() noexcept {
		
	}
}