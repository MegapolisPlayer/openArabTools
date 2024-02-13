#include "LightColor.hpp"

namespace OpenArabTools {
	namespace Internal {
		//Sets correct colors based on enum
		static void	SetInternalLightcolor(LightColor* const aLC, const LightColorD aLCD) noexcept {
			switch (aLCD) {
			case(LIGHTCOLOR_BLACK):              aLC->RGB255(0,   0,   0  ); return;
			case(LIGHTCOLOR_BLUE):               aLC->RGB255(0,   0,   255); return;
			case(LIGHTCOLOR_CYAN):               aLC->RGB255(0,   255, 255); return;
			case(LIGHTCOLOR_DARK_GRAY):          aLC->RGB255(64,  64,  64 ); return;
			case(LIGHTCOLOR_GRAY):               aLC->RGB255(128, 128, 128); return;
			case(LIGHTCOLOR_GREEN):              aLC->RGB255(0,   255, 0  ); return;
			case(LIGHTCOLOR_CHESSBOARD_BLACK):   aLC->RGB255(0,   0,   0  ); return;
			case(LIGHTCOLOR_CHESSBOARD_DARK):    aLC->RGB255(128, 64,  0  ); return;
			case(LIGHTCOLOR_CHESSBOARD_LIGHT):   aLC->RGB255(255, 192, 128); return;
			case(LIGHTCOLOR_CHESSBOARD_WHITE):   aLC->RGB255(255, 255, 255); return;
			case(LIGHTCOLOR_LIGHT_GRAY):         aLC->RGB255(192, 192, 192); return;
			case(LIGHTCOLOR_MAGENTA):            aLC->RGB255(128, 0,   128); return;
			case(LIGHTCOLOR_ORANGE):             aLC->RGB255(255, 128, 0  ); return;
			case(LIGHTCOLOR_PINK):               aLC->RGB255(255, 0,   255); return;
			case(LIGHTCOLOR_RED):                aLC->RGB255(255, 0,   0  ); return;
			case(LIGHTCOLOR_TRAFFIC_GREEN_OFF):  aLC->RGB255(0,   64,  0  ); return;
			case(LIGHTCOLOR_TRAFFIC_GREEN_ON):   aLC->RGB255(0,   255, 0  ); return;
			case(LIGHTCOLOR_TRAFFIC_RED_OFF):    aLC->RGB255(64,  0,   0  ); return;
			case(LIGHTCOLOR_TRAFFIC_RED_ON):     aLC->RGB255(255, 0,   0  ); return;
			case(LIGHTCOLOR_TRAFFIC_YELLOW_OFF): aLC->RGB255(64,  64,  0  ); return;
			case(LIGHTCOLOR_TRAFFIC_YELLOW_ON):  aLC->RGB255(255, 255, 0  ); return;
			case(LIGHTCOLOR_WHITE):              aLC->RGB255(255, 255, 255); return;
			case(LIGHTCOLOR_YELLOW):             aLC->RGB255(255, 255, 0  ); return;
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

	LightColor::LightColor(const float aR, const float aG, const float aB) noexcept
	: R(aR), G(aG), B(aB) {}

	LightColor& LightColor::Set(const LightColorD aColor) noexcept {
		Internal::SetInternalLightcolor(this, aColor);
		return *this;
	}

	LightColor& LightColor::LightColor::RGB(const float aR, const float aG, const float aB) noexcept {
		this->R = aR; this->G = aG; this->B = aB;
		return *this;
	}

	LightColor& LightColor::RGB255(const U08 aR, const U08 aG, const U08 aB) noexcept {
		this->R = float(aR) / 255.0;
		this->G = float(aG) / 255.0;
		this->B = float(aB) / 255.0;
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