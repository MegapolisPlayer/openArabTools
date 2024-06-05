#include "LightColor.hpp"

namespace OpenArabTools {
	namespace Internal {
		//Sets correct colors based on enum (LightColorD)
		static void	SetInternalLightcolor(LightColor* const apLC, const LightColorD aLCD) noexcept {
			switch (aLCD) {
			case(LIGHTCOLOR_BLACK):              apLC->RGB255(0, 0, 0); return;
			case(LIGHTCOLOR_BLUE):               apLC->RGB255(0, 0, 255); return;
			case(LIGHTCOLOR_CYAN):               apLC->RGB255(0, 255, 255); return;
			case(LIGHTCOLOR_DARK_GRAY):          apLC->RGB255(64, 64, 64); return;
			case(LIGHTCOLOR_GRAY):               apLC->RGB255(128, 128, 128); return;
			case(LIGHTCOLOR_GREEN):              apLC->RGB255(0, 255, 0); return;
			case(LIGHTCOLOR_CHESSBOARD_BLACK):   apLC->RGB255(0, 0, 0); return;
			case(LIGHTCOLOR_CHESSBOARD_DARK):    apLC->RGB255(128, 64, 0); return;
			case(LIGHTCOLOR_CHESSBOARD_LIGHT):   apLC->RGB255(255, 192, 128); return;
			case(LIGHTCOLOR_CHESSBOARD_WHITE):   apLC->RGB255(255, 255, 255); return;
			case(LIGHTCOLOR_LIGHT_GRAY):         apLC->RGB255(192, 192, 192); return;
			case(LIGHTCOLOR_MAGENTA):            apLC->RGB255(128, 0, 128); return;
			case(LIGHTCOLOR_ORANGE):             apLC->RGB255(255, 128, 0); return;
			case(LIGHTCOLOR_PINK):               apLC->RGB255(255, 0, 255); return;
			case(LIGHTCOLOR_RED):                apLC->RGB255(255, 0, 0); return;
			case(LIGHTCOLOR_TRAFFIC_GREEN_OFF):  apLC->RGB255(0, 64, 0); return;
			case(LIGHTCOLOR_TRAFFIC_GREEN_ON):   apLC->RGB255(0, 255, 0); return;
			case(LIGHTCOLOR_TRAFFIC_RED_OFF):    apLC->RGB255(64, 0, 0); return;
			case(LIGHTCOLOR_TRAFFIC_RED_ON):     apLC->RGB255(255, 0, 0); return;
			case(LIGHTCOLOR_TRAFFIC_YELLOW_OFF): apLC->RGB255(64, 64, 0); return;
			case(LIGHTCOLOR_TRAFFIC_YELLOW_ON):  apLC->RGB255(255, 255, 0); return;
			case(LIGHTCOLOR_WHITE):              apLC->RGB255(255, 255, 255); return;
			case(LIGHTCOLOR_YELLOW):             apLC->RGB255(255, 255, 0); return;
			}
		}

		//Sets correct colors from extended enum (LightColorEx)
		static void	SetInternalLightcolor(LightColor* const apLC, const LightColorEx aLCEx) noexcept {
			switch (aLCEx) {
			case(LIGHTCOLOREX_DARK_GREEN):            apLC->RGB255(0, 128, 0); return;
			case(LIGHTCOLOREX_DARKER_GREEN):          apLC->RGB255(0, 64, 0); return;
			case(LIGHTCOLOREX_LIGHT_BLUE):            apLC->RGB255(0, 255, 255); return;
			case(LIGHTCOLOREX_DARK_BLUE):             apLC->RGB255(0, 0, 128); return;
			case(LIGHTCOLOREX_CESKEDRAHY_LIGHT_BLUE): apLC->RGB255(0, 124, 176); return;
			case(LIGHTCOLOREX_CESKEDRAHY_DARK_BLUE):  apLC->RGB255(31, 56, 85); return;
			case(LIGHTCOLOREX_ERROR_COLOR):			  apLC->RGB255(179, 0, 179); return;
			}
		}
	}

	LightColor::LightColor() noexcept 
	: R(0.0), G(0.0), B(0.0) {}

	LightColor::LightColor(const LightColorD aColor) noexcept
	: R(0.0), G(0.0), B(0.0) {
		//initializer list to make compiler go away, this function sets it
		Internal::SetInternalLightcolor(this, aColor);
	}
	LightColor::LightColor(const LightColorEx aColor) noexcept
	: R(0.0), G(0.0), B(0.0) {
		Internal::SetInternalLightcolor(this, aColor);
	}

	LightColor::LightColor(const float aR, const float aG, const float aB) noexcept
	: R(aR), G(aG), B(aB) {}

	LightColor& LightColor::Set(const LightColorD aColor) noexcept {
		Internal::SetInternalLightcolor(this, aColor);
		return *this;
	}
	LightColor& LightColor::Set(const LightColorEx aColor) noexcept {
		Internal::SetInternalLightcolor(this, aColor);
		return *this;
	}

	LightColor& LightColor::LightColor::RGB(const float aR, const float aG, const float aB) noexcept {
		this->R = aR; this->G = aG; this->B = aB;
		return *this;
	}

	LightColor& LightColor::RGB255(const U08 aR, const U08 aG, const U08 aB) noexcept {
		this->R = float(aR) / 255.0f;
		this->G = float(aG) / 255.0f;
		this->B = float(aB) / 255.0f;
		return *this;
	}

	LightColor& LightColor::Darken() noexcept {
		//decrements by 25 IF value is bigger than 25, otherwise sets it to 0
		this->R -= ((this->R >= 25) ? 25 : this->R);
		this->G -= ((this->G >= 25) ? 25 : this->G);
		this->B -= ((this->B >= 25) ? 25 : this->B);
		return *this;
	}

	LightColor& LightColor::Lighten() noexcept {
		this->R += 25; this->G += 25; this->B += 25;
		if (this->R > 255) this->R = 255;
		if (this->G > 255) this->G = 255;
		if (this->B > 255) this->B = 255;
		return *this;
	}

	LightColor& LightColor::operator=(const LightColor& aColor) noexcept {
		this->R = aColor.R;
		this->G = aColor.G;
		this->B = aColor.B;
		return *this;
	}

	bool LightColor::operator==(const LightColor& aOther) const noexcept {
		return (this->R == aOther.R && this->G == aOther.G && this->B == aOther.B);
	}

	LightColor::~LightColor() noexcept {}
}