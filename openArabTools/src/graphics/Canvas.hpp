#pragma once
#include "internal/GLInterface.hpp"

namespace OpenArabTools {
	struct OPENARABTOOLS_OBJ Shape {
		uint64_t X, Y;
		LightColor Color;
		uint64_t Id;
		bool FilledIn;
	};

	struct OPENARABTOOLS_OBJ Square : public Shape {
		uint64_t SizeX, SizeY;
	};
	struct OPENARABTOOLS_OBJ Circle : public Shape {
		uint64_t Radius;
	};

	class OPENARABTOOLS_OBJ Canvas {
	public:
		Canvas() noexcept;

		void add() noexcept;
		void remove() noexcept;
		void clear() noexcept;

		void setBackground() noexcept;

		//
		// OpenArabTools necessities
		//

		bool open() const noexcept;
		bool update() noexcept;
		void run() noexcept;

		//
		// OpenArabTools extensions
		//

		void setColor() noexcept;

		void setTitle(const std::string& aTitle) noexcept;

		void showWindowAndRun() noexcept;
		bool sleep(const uint64_t aMs) noexcept;

		~Canvas() noexcept;
	private:
		Internal::GLWindow mWindow;
		std::vector<Shape> mShapes;
		LightColor mFG, mBG;
	};
}