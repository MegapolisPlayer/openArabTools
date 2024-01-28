#include "LightColor.hpp"

namespace OpenArabTools {
	namespace Internal {
		//Sets from enum to provided ints as pointers
		static void	SetInternalLightcolor(LightColor* const aLC, LightColorD aLCD) noexcept {
			switch (aLCD) {
			case(LIGHTCOLOR_BLACK):             aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_BLUE):              aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_CYAN):              aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_DARK_GRAY):         aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_GRAY):              aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_GREEN):             aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_CHESSBOARD_BLACK):  aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_CHESSBOARD_DARK):   aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_CHESSBOARD_LIGHT):  aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_CHESSBOARD_WHITE):  aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_LIGHT_GRAY):        aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_MAGENTA):           aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_ORANGE):            aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_PINK):              aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_RED):               aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_TRAFFIC_GREEN_OFF): aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_TRAFFIC_GREEN_ON):  aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_TRAFFIC_RED_OFF):   aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_TRAFFIC_RED_ON):    aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_YELLOW_OFF):        aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_YELLOW_ON):         aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_WHITE):             aLC->RGB255(0, 0, 0); break;
			case(LIGHTCOLOR_YELLOW):            aLC->RGB255(0, 0, 0); break;
			}
		}
	}

	LightColor::LightColor() noexcept {
		this->R = 0.0; 
		this->G = 0.0;
		this->B = 0.0;
	}

	LightColor::LightColor(const LightColorD aColor) noexcept {
		Internal::SetInternalLightcolor(this, aColor);
	}

	LightColor::LightColor(const Dec aR, const Dec aG, const Dec aB) noexcept {

	}

	LightColor* LightColor::Set(const LightColorD aColor) noexcept {
		return this;
	}

	LightColor* LightColor::LightColor::RGB(const Dec aR, const Dec aG, const Dec aB) noexcept {
		return this;
	}

	LightColor* LightColor::RGB255(const U08 aR, const U08 aG, const U08 aB) noexcept {
		return this;
	}

	LightColor* LightColor::Darken() noexcept {
		return this;
	}

	LightColor* LightColor::Lighten() noexcept {
		return this;
	}

	LightColor* LightColor::operator=(const LightColor aColor) noexcept {
		return this;
	}

	LightColor::~LightColor() noexcept {
	
	}
}