#pragma once
#include "Matrix.hpp"

namespace OpenArabTools {
	//A class showing a simple 3x3 dice with some configuration options.
	class OPENARABTOOLS_OBJ Dice {
	public:
		Dice();
		Dice(const uint64_t aSpace);
		Dice(const uint64_t aSpace, const uint64_t aBorder);

		void showWindow() noexcept;
		void hideWindow() noexcept;

		void setValue(const uint64_t aValue) noexcept;
		uint64_t getValue(const uint64_t aValue) const noexcept;

		//
		// OpenArabTools necessities
		//

		bool open() const noexcept;
		bool update() noexcept;
		void run() noexcept;

		//
		// OpenArabTools extensions
		//

		void setBackground(const LightColor& aLC) noexcept;
		void setColor(const LightColor& aLC) noexcept;

		void disableAll() noexcept;
		void enableAll() noexcept;

		void setTitle(const std::string& aTitle) noexcept;

		void showWindowAndRun() noexcept;
		bool sleep(const uint64_t aMs) noexcept;

		~Dice();
	private:
		Matrix mMatrix;
		uint64_t mValue, mSpace, mBorder;
	};
}