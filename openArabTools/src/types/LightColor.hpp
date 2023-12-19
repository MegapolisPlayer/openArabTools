#pragma once
#include "../Utils.hpp"

namespace OpenArabTools {
	//LightColor defined colors
	enum struct LightColorD {
		LIGHTCOLOR_RED,
		LIGHTCOLOR_BLUE,
		//TODO: finish
	};

	//LightColor structure
	struct OPENARABTOOLS_OBJ LightColor {
		Dec R = 0.0, G = 0.0, B = 0.0;

		void RGB(const Dec aR, const Dec aG, const Dec aB) noexcept;

		void Darken();

		void Lighten();

		LightColor& operator=(LightColorD aColor) noexcept;

		OPENARABTOOLS_EXTENSION(void RGB255(const U08 aR, const U08 aG, const U08 aB) noexcept);
	};
}