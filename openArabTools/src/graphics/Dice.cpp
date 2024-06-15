#include "Dice.hpp"

namespace OpenArabTools {
	Dice::Dice()
		: mValue(0), mSpace(0), mBorder(0) {
		this->mMatrix.set(3, 3);
		this->mMatrix.setBackground(LIGHTCOLOR_LIGHT_GRAY);
		this->mMatrix.setColor(LIGHTCOLOR_BLACK);
	}
	Dice::Dice(const uint64_t aSpace)
		: mValue(0), mSpace(aSpace), mBorder(0) {
		this->mMatrix.set(3 + (2 * aSpace), 3 + (2 * aSpace));
		this->mMatrix.setBackground(LIGHTCOLOR_LIGHT_GRAY);
		this->mMatrix.setColor(LIGHTCOLOR_BLACK);
	}
	Dice::Dice(const uint64_t aSpace, const uint64_t aBorder)
		: mValue(0), mSpace(aSpace), mBorder(aBorder) {
		this->mMatrix.set(3 + (aBorder * 2) + (2 * aSpace), 3 + (aBorder * 2) + (2 * aSpace));
		this->mMatrix.setBackground(LIGHTCOLOR_LIGHT_GRAY);
		this->mMatrix.setColor(LIGHTCOLOR_BLACK);
	}

	void Dice::showWindow() noexcept {
		this->mMatrix.showWindow();
	}
	void Dice::hideWindow() noexcept {
		this->mMatrix.hideWindow();
	}

	//column, row wrappers...
	#define CRWRAPPER(col, row) (this->mBorder + col + (col * this->mSpace)), (this->mBorder + row + (row * this->mSpace))

	void Dice::setValue(const uint64_t aValue) noexcept {
		if (aValue > 9) {
			//cannot be under 0: we take in unsigned value
			Error::error("Value in Dice is out of range. (Value must be in range 0-9)");
		}

		this->disableAll(); //reset

		this->mValue = aValue;
		if (this->mValue == 0) { return; } //we already disabled all
		if (this->mValue == 9) { this->enableAll(); return; } //just enable everything and dont bother

		if (this->mValue >= 2) { this->mMatrix.setOn(CRWRAPPER(0, 0)); } //2,3,4,5,6,7,8
		if (this->mValue >= 6) { this->mMatrix.setOn(CRWRAPPER(0, 1)); } //6,7,8
		if (this->mValue >= 4) { this->mMatrix.setOn(CRWRAPPER(0, 2)); } //4,5,6,7,8
		if (this->mValue == 8) { this->mMatrix.setOn(CRWRAPPER(1, 0)); } //8
		if (this->mValue % 2) { this->mMatrix.setOn(CRWRAPPER(1, 1)); } //1,3,5,7
		if (this->mValue == 8) { this->mMatrix.setOn(CRWRAPPER(1, 2)); } //8
		if (this->mValue >= 4) { this->mMatrix.setOn(CRWRAPPER(2, 0)); } //4,5,6,7,8
		if (this->mValue >= 6) { this->mMatrix.setOn(CRWRAPPER(2, 1)); } //6,7,8
		if (this->mValue >= 2) { this->mMatrix.setOn(CRWRAPPER(2, 2)); } //2,3,4,5,6,7,8
	}
	uint64_t Dice::getValue(const uint64_t aValue) const noexcept {
		return this->mValue;
	}

	bool Dice::open() const noexcept {
		return this->mMatrix.open();
	}
	bool Dice::update() noexcept {
		return this->mMatrix.update();
	}
	void Dice::run() noexcept {
		return this->mMatrix.run();
	}

	void Dice::setBackground(const LightColor& aLC) noexcept {
		this->mMatrix.setBackground(aLC);
	}
	void Dice::setColor(const LightColor& aLC) noexcept {
		this->mMatrix.setColor(aLC);
	}

	void Dice::disableAll() noexcept {
		for (uint64_t i = 0; i < this->mMatrix.getSize(); i++) {
			this->mMatrix.setOff(i);
		}
		this->mValue = 0;
	}
	void Dice::enableAll() noexcept {
		for (uint64_t row = 0; row < 3; row++) {
			for (uint64_t col = 0; col < 3; col++) {
				this->mMatrix.setOn(
					this->mBorder + col + (col * this->mSpace),
					this->mBorder + row + (row * this->mSpace)
				);
			}
		}
		this->mValue = 9;
	}

	void Dice::setTitle(const std::string& aTitle) noexcept {
		this->mMatrix.setTitle(aTitle);
	}
		
	void Dice::showWindowAndRun() noexcept {
		this->mMatrix.showWindowAndRun();
	}
	bool Dice::sleep(const uint64_t aMs) noexcept {
		return this->mMatrix.sleep(aMs);
	}

	Dice::~Dice() {}
}