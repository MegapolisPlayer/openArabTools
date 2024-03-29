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

	//LightColor structure
	struct OPENARABTOOLS_OBJ LightColor {
		float R, G, B;

		LightColor() noexcept;

		LightColor (const LightColorD aColor) noexcept;

		LightColor (const float aR, const float aG, const float aB) noexcept;

		LightColor& Set(const LightColorD aColor) noexcept;

		LightColor& RGB(const float aR, const float aG, const float aB) noexcept;

		LightColor& RGB255(const U08 aR, const U08 aG, const U08 aB) noexcept;

		LightColor& Darken() noexcept;

		LightColor& Lighten() noexcept;

		LightColor& operator=(const LightColor& aColor) noexcept;

		bool operator==(const LightColor& aOther) const noexcept;

		~LightColor() noexcept;
	};
}