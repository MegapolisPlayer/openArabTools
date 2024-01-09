#include "LightColor.hpp"

namespace OpenArabTools {
	namespace Internal {
		//Sets from enum to provided ints as pointers
		static void	SetInternalLightcolor() noexcept {

		}
	}

	LightColor::LightColor(const LightColorD aColor) noexcept {

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

	LightColor* LightColor::Darken() {
		return this;
	}

	LightColor* LightColor::Lighten() {
		return this;
	}

	LightColor* LightColor::operator=(const LightColor aColor) noexcept {
		return this;
	}

	LightColor::~LightColor() noexcept {
	
	}
}