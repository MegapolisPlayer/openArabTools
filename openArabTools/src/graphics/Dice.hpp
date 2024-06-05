#pragma once
#include "Matrix.hpp"

namespace OpenArabTools {
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