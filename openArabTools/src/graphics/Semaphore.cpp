#include "Semaphore.hpp"

namespace OpenArabTools {
	Semaphore::Semaphore() noexcept {
		this->mMatrix.set(1, 3);
		this->mMatrix.setOffColor(0, LightColor(LIGHTCOLOR_TRAFFIC_RED_OFF));
		this->mMatrix.setOffColor(1, LightColor(LIGHTCOLOR_TRAFFIC_YELLOW_OFF));
		this->mMatrix.setOffColor(2, LightColor(LIGHTCOLOR_TRAFFIC_GREEN_OFF));
		this->mMatrix.setColor(0, LightColor(LIGHTCOLOR_TRAFFIC_RED_ON));
		this->mMatrix.setColor(1, LightColor(LIGHTCOLOR_TRAFFIC_YELLOW_ON));
		this->mMatrix.setColor(2, LightColor(LIGHTCOLOR_TRAFFIC_GREEN_ON));
		this->mIsFlipped = false;
		this->mIsRedOn = false;
		this->mIsYellowOn = false;
		this->mIsGreenOn = false;
	}

	Semaphore::Semaphore(SemaphoreOrientation aOrientation) noexcept {
		this->mIsRedOn = false;
		this->mIsYellowOn = false;
		this->mIsGreenOn = false;

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

		if (!this->mIsFlipped) {
			this->mMatrix.setOffColor(0, LightColor(LIGHTCOLOR_TRAFFIC_RED_OFF));
			this->mMatrix.setOffColor(1, LightColor(LIGHTCOLOR_TRAFFIC_YELLOW_OFF));
			this->mMatrix.setOffColor(2, LightColor(LIGHTCOLOR_TRAFFIC_GREEN_OFF));
			this->mMatrix.setColor(0, LightColor(LIGHTCOLOR_TRAFFIC_RED_ON));
			this->mMatrix.setColor(1, LightColor(LIGHTCOLOR_TRAFFIC_YELLOW_ON));
			this->mMatrix.setColor(2, LightColor(LIGHTCOLOR_TRAFFIC_GREEN_ON));
		}
		else {
			this->mMatrix.setOffColor(2, LightColor(LIGHTCOLOR_TRAFFIC_RED_OFF));
			this->mMatrix.setOffColor(1, LightColor(LIGHTCOLOR_TRAFFIC_YELLOW_OFF));
			this->mMatrix.setOffColor(0, LightColor(LIGHTCOLOR_TRAFFIC_GREEN_OFF));
			this->mMatrix.setColor(2, LightColor(LIGHTCOLOR_TRAFFIC_RED_ON));
			this->mMatrix.setColor(1, LightColor(LIGHTCOLOR_TRAFFIC_YELLOW_ON));
			this->mMatrix.setColor(0, LightColor(LIGHTCOLOR_TRAFFIC_GREEN_ON));
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
		this->mMatrix.setOn((this->mIsFlipped) ? 2 : 0);
		this->mIsRedOn = true;
	}
	void Semaphore::setYellowOn() noexcept {
		this->mMatrix.setOn(1);
		this->mIsYellowOn = true;
	}
	void Semaphore::setGreenOn() noexcept {
		this->mMatrix.setOn(this->mIsFlipped ? 0 : 2);
		this->mIsGreenOn = true;
	}

	void Semaphore::setRedOff() noexcept {
		this->mMatrix.setOff(this->mIsFlipped ? 2 : 0);
		this->mIsRedOn = false;
	}
	void Semaphore::setYellowOff() noexcept {
		this->mMatrix.setOff(1);
		this->mIsYellowOn = false;
	}
	void Semaphore::setGreenOff() noexcept {
		this->mMatrix.setOff(this->mIsFlipped ? 0 : 2);
		this->mIsGreenOn = false;
	}

	void Semaphore::setRedOnOff(const bool aOnOff) noexcept {
		this->mMatrix.setOnOff(this->mIsFlipped ? 2 : 0, aOnOff);
		this->mIsRedOn = aOnOff;
	}
	void Semaphore::setYellowOnOff(const bool aOnOff) noexcept {
		this->mMatrix.setOnOff(1, aOnOff);
		this->mIsYellowOn = aOnOff;
	}
	void Semaphore::setGreenOnOff(const bool aOnOff) noexcept {
		this->mMatrix.setOnOff(this->mIsFlipped ? 0 : 2, aOnOff);
		this->mIsGreenOn = aOnOff;
	}

	std::string Semaphore::getTitle() const noexcept {
		return this->mMatrix.getTitle();
	}
	bool Semaphore::isRedOn() const noexcept {
		return this->mIsRedOn;
	}
	bool Semaphore::isYellowOn() const noexcept {
		return this->mIsYellowOn;
	}
	bool Semaphore::isGreenOn() const noexcept {
		return this->mIsGreenOn;
	}

	void Semaphore::toggleRed() noexcept {
		this->mIsRedOn = !this->mIsRedOn;
		this->mMatrix.setOnOff(this->mIsFlipped ? 2 : 0, this->mIsRedOn);
	}
	void Semaphore::toggleYellow() noexcept {
		this->mIsYellowOn = !this->mIsYellowOn;
		this->mMatrix.setOnOff(1, this->mIsYellowOn);
	}
	void Semaphore::toggleGreen() noexcept {
		this->mIsGreenOn = !this->mIsGreenOn;
		this->mMatrix.setOnOff(this->mIsFlipped ? 0 : 2, this->mIsGreenOn);
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

	bool Semaphore::sleep(const U64 aMs) noexcept {
		return this->mMatrix.sleep(aMs);
	}

	Semaphore::~Semaphore() noexcept {}
}