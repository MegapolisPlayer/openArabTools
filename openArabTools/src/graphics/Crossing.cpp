#include "Crossing.hpp"

namespace OpenArabTools {
	CrossingSemaphoreAccessor::CrossingSemaphoreAccessor(Crossing* aParent, const uint64_t aSemaphoreId) noexcept
	: mParent(nullptr), mSemaphoreId(INT64_MAX) {
		if (aSemaphoreId >= 4) {
			Error::error("Semaphore id out of range in accessor: delete this accessor. (This will cause an error otherwise.)"); 
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
		this->mParent->mMatrix.setOnOff(this->mParent->mSemaphoreInfo[this->mSemaphoreId].RedX, this->mParent->mSemaphoreInfo[this->mSemaphoreId].RedY, aOnOff);
	}
	void CrossingSemaphoreAccessor::setYellowOnOff(const bool aOnOff) noexcept {
		this->mParent->mMatrix.setOnOff(this->mParent->mSemaphoreInfo[this->mSemaphoreId].YellowX, this->mParent->mSemaphoreInfo[this->mSemaphoreId].YellowY, aOnOff);
	}
	void CrossingSemaphoreAccessor::setGreenOnOff(const bool aOnOff) noexcept {
		this->mParent->mMatrix.setOnOff(this->mParent->mSemaphoreInfo[this->mSemaphoreId].GreenX, this->mParent->mSemaphoreInfo[this->mSemaphoreId].GreenY, aOnOff);
	}

	bool CrossingSemaphoreAccessor::isRedOn() const noexcept {
		return this->mParent->mMatrix.isOn(this->mParent->mSemaphoreInfo[this->mSemaphoreId].RedX, this->mParent->mSemaphoreInfo[this->mSemaphoreId].RedY);
	}
	bool CrossingSemaphoreAccessor::isYellowOn() const noexcept {
		return this->mParent->mMatrix.isOn(this->mParent->mSemaphoreInfo[this->mSemaphoreId].YellowX, this->mParent->mSemaphoreInfo[this->mSemaphoreId].YellowY);
	}
	bool CrossingSemaphoreAccessor::isGreenOn() const noexcept {
		return this->mParent->mMatrix.isOn(this->mParent->mSemaphoreInfo[this->mSemaphoreId].GreenX, this->mParent->mSemaphoreInfo[this->mSemaphoreId].GreenY);
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
	static constexpr const uint64_t sCrossingStandardSizeX = 30;
	static constexpr const uint64_t sCrossingStandardSizeY = 30;

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
		"GGGGGGGGGB2BGPRRPGBBBBBGGGGGGG"
		"GGGGGGGGGB1BGPRRPGB123BGGGGGGG"
		"GGGGGGGGGBBBGPRRPGBBBBBGGGGGGG"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"PPPPPPPPPPPPPPRRPPPPPPPPPPPPPP"
		"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"
		"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"
		"PPPPPPPPPPPPPPRRPPPPPPPPPPPPPP"
		"GGGGGGGGGGGGGPRRPGGGGGGGGGGGGG"
		"GGGGGGGBBBBBGPRRPGBBBGGGGGGGGG"
		"GGGGGGGB321BGPRRPGB1BGGGGGGGGG"
		"GGGGGGGBBBBBGPRRPGB2BGGGGGGGGG"
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
		this->mSemaphoreInfo = {};

		//Draw 4-way crossing using matrix background and foreground

		this->mMatrix.setBackground(LIGHTCOLOR_GREEN);

		this->drawFromString(DefaultCrossingStyle);
	}
	Crossing::Crossing(const std::string& aFilename) noexcept {
		this->mMatrix.set(sCrossingStandardSizeX, sCrossingStandardSizeY);
		this->mSemaphoreInfo = {};

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

	//shared pointer contained also in the main crossing class

	CrossingSemaphoreAccessor* const Crossing::getSemaphore(const uint64_t aId) noexcept {
		if (aId >= 4) { Error::error("Semaphore ID out of range"); return {}; }
		this->mAccessors.push_back(new CrossingSemaphoreAccessor(this, aId));
		return this->mAccessors.back();
	}

	void Crossing::showSemaphore(const uint64_t aId) noexcept {
		if (aId >= 4) { Error::error("Semaphore ID out of range"); return; }

		
	}
	void Crossing::hideSemaphore(const uint64_t aId) noexcept {
		if (aId >= 4) { Error::error("Semaphore ID out of range"); return; }

		//disable (make invisible) lights
		
		this->mMatrix.setColorAlpha(this->mSemaphoreInfo[aId].RedX, this->mSemaphoreInfo[aId].RedY, 0.0f);
		this->mMatrix.setOffColorAlpha(this->mSemaphoreInfo[aId].RedX, this->mSemaphoreInfo[aId].RedY, 0.0f);

		this->mMatrix.setColorAlpha(this->mSemaphoreInfo[aId].YellowX, this->mSemaphoreInfo[aId].YellowY, 0.0f);
		this->mMatrix.setOffColorAlpha(this->mSemaphoreInfo[aId].YellowX, this->mSemaphoreInfo[aId].YellowY, 0.0f);

		this->mMatrix.setColorAlpha(this->mSemaphoreInfo[aId].GreenX, this->mSemaphoreInfo[aId].GreenY, 0.0f);
		this->mMatrix.setOffColorAlpha(this->mSemaphoreInfo[aId].GreenX, this->mSemaphoreInfo[aId].GreenY, 0.0f);

		//reset everything around them
		for (int8_t x = -1; x <= 1; x++) {
			for (int8_t y = -1; y <= 1; y++) {
				uint64_t MatrixWidth = this->mMatrix.getWidth();
				uint64_t MatrixHeight = this->mMatrix.getHeight();
				if(this->mSemaphoreInfo[aId].RedX + x < 0     || this->mSemaphoreInfo[aId].RedX + x >= MatrixWidth ||
					this->mSemaphoreInfo[aId].RedY + y < 0    || this->mSemaphoreInfo[aId].RedY + y >= MatrixHeight ||
					this->mSemaphoreInfo[aId].YellowX + x < 0 || this->mSemaphoreInfo[aId].YellowX + x >= MatrixWidth ||
					this->mSemaphoreInfo[aId].YellowY + y < 0 || this->mSemaphoreInfo[aId].YellowY + y >= MatrixHeight ||
					this->mSemaphoreInfo[aId].GreenX + x < 0  || this->mSemaphoreInfo[aId].GreenX + x >= MatrixWidth ||
					this->mSemaphoreInfo[aId].GreenY + y < 0  || this->mSemaphoreInfo[aId].GreenY + y >= MatrixHeight) {
					continue;
				}

				this->mMatrix.setBackground(this->mSemaphoreInfo[aId].RedX + x, this->mSemaphoreInfo[aId].RedY + y, LIGHTCOLOREX_DARK_GREEN);
				this->mMatrix.setBackground(this->mSemaphoreInfo[aId].YellowX + x, this->mSemaphoreInfo[aId].YellowY + y, LIGHTCOLOREX_DARK_GREEN);
				this->mMatrix.setBackground(this->mSemaphoreInfo[aId].GreenX + x, this->mSemaphoreInfo[aId].GreenY + y, LIGHTCOLOREX_DARK_GREEN);
			}
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
	bool Crossing::sleep(const uint64_t aMs) noexcept {
		return this->mMatrix.sleep(aMs);
	}

	Crossing::~Crossing() noexcept {
		for (CrossingSemaphoreAccessor* Accessor : this->mAccessors) {
			delete Accessor;
		}
	}

	//helper - quadrants:
	//01 //+1 from right
	//23 //+2 from bottom
	uint64_t Crossing::getQuadrantId(const uint64_t aId) noexcept {
		// from right + 2(from bottom)
		return uint64_t((aId % this->mMatrix.getWidth()) >= this->mMatrix.getWidth() / 2) + (2 * uint64_t((aId / this->mMatrix.getWidth()) >= this->mMatrix.getHeight() / 2));
	}

	void Crossing::drawFromString(const std::string& aString) noexcept {
		//most tiles will probably be grass
		this->mMatrix.setBackground(LIGHTCOLOREX_DARK_GREEN);

		//Draw from string
		//G - Grass, R - Road, W - White, B - Black, 1 - Red, 2 - Yellow, 3 - Green

		for (uint64_t Id = 0; Id < aString.size(); Id++) {
			switch (aString[Id]) {
				case('G'):
					//randomize grass color
					if (Utils::getRandomBool()) {
						this->mMatrix.setBackground(Id, LIGHTCOLOREX_DARKER_GREEN);
					}
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
					this->mMatrix.setOn(Id); //default: red on

					this->mSemaphoreInfo[this->getQuadrantId(Id)].RedX = (Id % this->mMatrix.getWidth());
					this->mSemaphoreInfo[this->getQuadrantId(Id)].RedY = uint64_t(Id / this->mMatrix.getWidth());
					this->mSemaphoreInfo[this->getQuadrantId(Id)].Hidden = false;
					break;
				case('2'):
					this->mMatrix.setBackground(Id, LIGHTCOLOR_BLACK);
					this->mMatrix.setOffColor(Id, LIGHTCOLOR_TRAFFIC_YELLOW_OFF);
					this->mMatrix.setColor(Id, LIGHTCOLOR_TRAFFIC_YELLOW_ON);

					this->mSemaphoreInfo[this->getQuadrantId(Id)].YellowX = (Id % this->mMatrix.getWidth());
					this->mSemaphoreInfo[this->getQuadrantId(Id)].YellowY = uint64_t(Id / this->mMatrix.getWidth());
					this->mSemaphoreInfo[this->getQuadrantId(Id)].Hidden = false;
					break;
				case('3'):
					this->mMatrix.setBackground(Id, LIGHTCOLOR_BLACK);
					this->mMatrix.setOffColor(Id, LIGHTCOLOR_TRAFFIC_GREEN_OFF);
					this->mMatrix.setColor(Id, LIGHTCOLOR_TRAFFIC_GREEN_ON);

					this->mSemaphoreInfo[this->getQuadrantId(Id)].GreenX = (Id % this->mMatrix.getWidth());
					this->mSemaphoreInfo[this->getQuadrantId(Id)].GreenY = uint64_t(Id / this->mMatrix.getWidth());
					this->mSemaphoreInfo[this->getQuadrantId(Id)].Hidden = false;
					break;
				default:
					this->mMatrix.setBackground(Id, LIGHTCOLOREX_ERROR_COLOR);
					break;
				
			}
		}
	}
}