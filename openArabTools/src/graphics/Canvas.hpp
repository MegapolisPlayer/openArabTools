#pragma once
#include "internal/GLInterface.hpp"

namespace OpenArabTools {
	struct OPENARABTOOLS_OBJ Shape {
		U64 X, Y;
		LightColor Color;
	};

	struct OPENARABTOOLS_OBJ Square : public Shape {
		U64 SizeX, SizeY;
	};
	struct OPENARABTOOLS_OBJ Circle : public Shape {
		U64 Radeon;
	};
	struct OPENARABTOOLS_OBJ Image : public Shape {
		U64 SizeX, SizeY, ImageWidth, ImageHeight;
	};

	class OPENARABTOOLS_OBJ Canvas {
	public:
		Canvas() noexcept;

		~Canvas() noexcept;
	private:
		Internal::GLWindow mWindow;
	};
}