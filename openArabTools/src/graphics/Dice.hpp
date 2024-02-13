#pragma once
#include "Matrix.hpp"

namespace OpenArabTools {
	class OPENARABTOOLS_OBJ Dice {
	public:
		Dice();
		Dice(U64 aSpace);
		Dice(U64 aSpace, U64 aBorder);

		void showWindow() noexcept;
		void hideWindow() noexcept;

		void setValue(U64 aValue) noexcept;
		U64 getValue(U64 aValue) const noexcept;

		//
		// OPENARABTOOLS necessities
		//

		bool open() const noexcept;
		bool update() noexcept;
		void run() noexcept;

		//
		// OPENARABTOOLS extensions
		//

		void disableAll() noexcept;
		void enableAll() noexcept;

		void showWindowAndRun() noexcept;
		bool sleep(const U64 aMs) noexcept;

		~Dice();
	private:
		Matrix mMatrix;
		U64 mValue, mSpace, mBorder;
	};
}