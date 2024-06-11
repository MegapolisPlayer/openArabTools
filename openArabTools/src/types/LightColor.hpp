#pragma once
#include "../Utils.hpp"

namespace OpenArabTools {
	//LightColor defined colors
	enum LightColorD : uint8_t {
		LIGHTCOLOR_BLACK = 0,
		LIGHTCOLOR_BLUE,
		LIGHTCOLOR_CYAN,
		LIGHTCOLOR_DARK_GRAY,
		LIGHTCOLOR_GRAY,
		LIGHTCOLOR_GREEN,
		LIGHTCOLOR_CHESSBOARD_BLACK,
		LIGHTCOLOR_CHESSBOARD_DARK,
		LIGHTCOLOR_CHESSBOARD_LIGHT,
		LIGHTCOLOR_CHESSBOARD_WHITE,
		LIGHTCOLOR_LIGHT_GRAY,
		LIGHTCOLOR_MAGENTA,
		LIGHTCOLOR_ORANGE,
		LIGHTCOLOR_PINK,
		LIGHTCOLOR_RED,
		LIGHTCOLOR_TRAFFIC_GREEN_OFF,
		LIGHTCOLOR_TRAFFIC_GREEN_ON,
		LIGHTCOLOR_TRAFFIC_RED_OFF,
		LIGHTCOLOR_TRAFFIC_RED_ON,
		LIGHTCOLOR_TRAFFIC_YELLOW_OFF,
		LIGHTCOLOR_TRAFFIC_YELLOW_ON,
		LIGHTCOLOR_WHITE,
		LIGHTCOLOR_YELLOW
	};

	//Extended LightColor colors
	enum LightColorEx : uint8_t {
		LIGHTCOLOREX_DARK_GREEN = (LIGHTCOLOR_YELLOW + 1),
		LIGHTCOLOREX_DARKER_GREEN,
		LIGHTCOLOREX_LIGHT_BLUE,
		LIGHTCOLOREX_DARK_BLUE,
		LIGHTCOLOREX_CESKEDRAHY_LIGHT_BLUE,
		LIGHTCOLOREX_CESKEDRAHY_DARK_BLUE,
		LIGHTCOLOREX_ERROR_COLOR
	};

	//LightColor structure
	struct OPENARABTOOLS_OBJ LightColor {
		//Individual R, G, and B values of the color.
		float R, G, B;

		LightColor() noexcept;
		LightColor(const LightColorD aColor) noexcept;
		LightColor(const LightColorEx aColor) noexcept;
		LightColor(const float aR, const float aG, const float aB) noexcept;
		LightColor(const uint8_t aR, const uint8_t aG, const uint8_t aB) noexcept;

		LightColor(const LightColor& aOther) noexcept;

		//Sets color from values in LightColorD
		LightColor& Set(const LightColorD aColor) noexcept;
		//Sets color from values in LightColorEx
		LightColor& Set(const LightColorEx aColor) noexcept;

		//Sets color from values in range 0-1
		LightColor& RGB(const float aR, const float aG, const float aB) noexcept;
		//Sets color from values in range 0-255
		LightColor& RGB255(const uint8_t aR, const uint8_t aG, const uint8_t aB) noexcept;

		//Makes color darker
		LightColor& Darken() noexcept;
		//Makes color lighter
		LightColor& Lighten() noexcept;

		LightColor& operator=(const LightColor& aOther) noexcept;
		bool operator==(const LightColor& aOther) const noexcept;

		~LightColor() noexcept;
	};
}