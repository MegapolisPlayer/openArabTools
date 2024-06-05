#pragma once
#include "internal/GLInterface.hpp"

namespace OpenArabTools {
	struct OPENARABTOOLS_OBJ Shape {
		uint64_t X, Y;
		LightColor Color;
	};

	struct OPENARABTOOLS_OBJ Square : public Shape {
		uint64_t SizeX, SizeY;
	};
	struct OPENARABTOOLS_OBJ Circle : public Shape {
		uint64_t Radeon;
	};
	struct OPENARABTOOLS_OBJ Image : public Shape {
		uint64_t SizeX, SizeY, ImageWidth, ImageHeight;
	};

	class OPENARABTOOLS_OBJ Canvas {
	public:
		Canvas() noexcept;

		~Canvas() noexcept;
	private:
		Internal::GLWindow mWindow;
	};
}