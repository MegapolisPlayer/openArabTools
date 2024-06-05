#include "Crossing.hpp"

namespace OpenArabTools {
	static constexpr U64 csSemaphoreRowSize = 4;
	static constexpr U64 csSemaphoreRedOffset = 1;
	static constexpr U64 csSemaphoreYellowOffset = 2;
	static constexpr U64 csSemaphoreGreenOffset = 3;

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
		this->mParent->mSemaphoreStates[(this->mSemaphoreId * csSemaphoreRowSize) + csSemaphoreRedOffset] = aOnOff;
	}
	void CrossingSemaphoreAccessor::setYellowOnOff(const bool aOnOff) noexcept {
		this->mParent->mSemaphoreStates[(this->mSemaphoreId * csSemaphoreRowSize) + csSemaphoreYellowOffset] = aOnOff;
	}
	void CrossingSemaphoreAccessor::setGreenOnOff(const bool aOnOff) noexcept {
		this->mParent->mSemaphoreStates[(this->mSemaphoreId * csSemaphoreRowSize) + csSemaphoreGreenOffset] = aOnOff;
	}

	bool CrossingSemaphoreAccessor::isRedOn() const noexcept {
		return this->mParent->mSemaphoreStates[(this->mSemaphoreId * csSemaphoreRowSize) + csSemaphoreRedOffset];
	}
	bool CrossingSemaphoreAccessor::isYellowOn() const noexcept {
		return this->mParent->mSemaphoreStates[(this->mSemaphoreId * csSemaphoreRowSize) + csSemaphoreYellowOffset];
	}
	bool CrossingSemaphoreAccessor::isGreenOn() const noexcept {
		return this->mParent->mSemaphoreStates[(this->mSemaphoreId * csSemaphoreRowSize) + csSemaphoreGreenOffset];
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

	//validation macros, set default size
	static constexpr const U64 sCrossingStandardSizeX = 30;
	static constexpr const U64 sCrossingStandardSizeY = 30;

	const char* DefaultCrossingStyle =
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGBBBGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGB3BGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGB2BGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGB1BGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGBBBGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"PPPPPPPPPPPPPPRRPPPPPPPPPPPPPP"
		"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"
		"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"
		"PPPPPPPPPPPPPPRRPPPPPPPPPPPPPP"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGBBBGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGB1BGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGB2BGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGB3BGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGBBBGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
	;

	Crossing::Crossing() noexcept {
		this->mMatrix.set(sCrossingStandardSizeX, sCrossingStandardSizeY);
		this->mSemaphoreStates = { false };

		//Draw 4-way crossing using matrix background and foreground

		this->mMatrix.setBackground(LIGHTCOLOR_GREEN);

		this->drawFromString(DefaultCrossingStyle);
	}
	Crossing::Crossing(const std::string& aFilename) noexcept {
		this->mMatrix.set(sCrossingStandardSizeX, sCrossingStandardSizeY);
		this->mSemaphoreStates = { false };

		std::ifstream File;
		File.open(aFilename, std::ios::binary);

		if (!File.is_open()) {
			Error::error("Provided Crossing information file does not exist.");
			return;
		}

		File.close();

		//this->drawFromString();
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

	//helper - quadrants:
	//01 //+1 from right
	//23 //+2 from bottom
	U64 Crossing::getQuadrantId(const U64 aX, const U64 aY) noexcept {
		// from right + 2(from bottom)
		return (aX >= this->mMatrix.getWidth() / 2) + (2 * (aY >= (this->mMatrix.getHeight() / 2)));
	}

	void Crossing::drawFromString(const std::string& aString) noexcept {
		//most tiles will probably be grass
		this->mMatrix.setBackground(LIGHTCOLOREX_DARK_GREEN);

		//Draw from string
		//G - Grass, R - Road, W - White, B - Black, 1 - Red, 2 - Yellow, 3 - Green

		for (U64 Id = 0; Id < aString.size(); Id++) {
			switch (aString[Id]) {
				case('G'):
					break;
				case('R'):
					this->mMatrix.setBackground(Id, LIGHTCOLOR_GRAY);
					break;
				case('P'):
					this->mMatrix.setBackground(Id, LIGHTCOLOR_LIGHT_GRAY);
					break;
				case('B'):
					this->mMatrix.setBackground(Id, LIGHTCOLOR_BLACK);
					break;

				case('1'):
					this->mMatrix.setBackground(Id, LIGHTCOLOR_BLACK);
					this->mMatrix.setOffColor(Id, LIGHTCOLOR_TRAFFIC_RED_OFF);
					this->mMatrix.setColor(Id, LIGHTCOLOR_TRAFFIC_RED_ON);
					break;
				case('2'):
					this->mMatrix.setBackground(Id, LIGHTCOLOR_BLACK);
					this->mMatrix.setOffColor(Id, LIGHTCOLOR_TRAFFIC_YELLOW_OFF);
					this->mMatrix.setColor(Id, LIGHTCOLOR_TRAFFIC_YELLOW_ON);
					break;
				case('3'):
					this->mMatrix.setBackground(Id, LIGHTCOLOR_BLACK);
					this->mMatrix.setOffColor(Id, LIGHTCOLOR_TRAFFIC_GREEN_OFF);
					this->mMatrix.setColor(Id, LIGHTCOLOR_TRAFFIC_GREEN_ON);
					break;
				default:
					this->mMatrix.setBackground(Id, LIGHTCOLOREX_ERROR_COLOR);
					break;
				
			}
		}
	}
}