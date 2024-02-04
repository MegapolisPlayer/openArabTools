#include "Semaphore.hpp"

namespace OpenArabTools {
	Semaphore::Semaphore() noexcept {
		this->mMatrix.set(1, 3);
		this->mMatrix.setColor(0, LightColor(LIGHTCOLOR_TRAFFIC_GREEN_OFF));
		this->mMatrix.setColor(1, LightColor(LIGHTCOLOR_TRAFFIC_YELLOW_OFF));
		this->mMatrix.setColor(2, LightColor(LIGHTCOLOR_TRAFFIC_RED_OFF));
		this->mIsFlipped = false;
	}

	Semaphore::Semaphore(SemaphoreOrientation aOrientation) noexcept {
		switch (aOrientation) {
		case(SemaphoreOrientation::UPSIDEDOWN):
			this->mMatrix.set(1, 3);
			this->mIsFlipped = true;
			break;
		case(SemaphoreOrientation::UPSIDELEFT):
			this->mMatrix.set(3, 1);
			this->mIsFlipped = false;
			break;
		case(SemaphoreOrientation::UPSIDERIGHT):
			this->mMatrix.set(3, 1);
			this->mIsFlipped = true;
			break;
		case(SemaphoreOrientation::NORMAL):
		default:
			this->mMatrix.set(1, 3);
			this->mIsFlipped = false;
			break;
		}
	}

	void Semaphore::setTitle(const std::string& aTitle) noexcept {
		this->mMatrix.setTitle(aTitle);
	}

	void Semaphore::showWindow() noexcept {
		this->mMatrix.showWindow();
	}
	void Semaphore::hideWindow() noexcept {
		this->mMatrix.hideWindow();
	}

	void Semaphore::setRedOn() noexcept {
		this->mMatrix.setOn(this->mIsFlipped ? 2 : 0);
	}
	void Semaphore::setYellowOn() noexcept {
		this->mMatrix.setOn(1);
	}
	void Semaphore::setGreenOn() noexcept {
		this->mMatrix.setOn(this->mIsFlipped ? 0 : 2);
	}

	void Semaphore::setRedOff() noexcept {
		this->mMatrix.setOff(this->mIsFlipped ? 0 : 2);
	}
	void Semaphore::setYellowOff() noexcept {
		this->mMatrix.setOff(1);
	}
	void Semaphore::setGreenOff() noexcept {
		this->mMatrix.setOff(this->mIsFlipped ? 2 : 0);
	}

	void Semaphore::setRedOnOff() noexcept {
		this->mMatrix.setOnOff(this->mIsFlipped ? 2 : 0);
	}
	void Semaphore::setYellowOnOff() noexcept {
		this->mMatrix.setOnOff(1);
	}
	void Semaphore::setGreenOnOff() noexcept {
		this->mMatrix.setOnOff(this->mIsFlipped ? 0 : 2);
	}

	std::string Semaphore::getTitle() noexcept {
		return this->mMatrix.getTitle();
	}
	bool Semaphore::isRedOn() noexcept {
		return this->mMatrix.isOn(this->mIsFlipped ? 2 : 0);
	}
	bool Semaphore::isYellowOn() noexcept {
		return this->mMatrix.isOn(1);
	}
	bool Semaphore::isGreenOn() noexcept {
		return this->mMatrix.isOn(this->mIsFlipped ? 0 : 2);
	}

	bool Semaphore::open() const noexcept {
		return this->mMatrix.open();
	}

	bool Semaphore::update() noexcept {
		return this->mMatrix.update();
	}

	void Semaphore::run() noexcept {
		this->mMatrix.run();
	}

	Semaphore::~Semaphore() noexcept {}
}