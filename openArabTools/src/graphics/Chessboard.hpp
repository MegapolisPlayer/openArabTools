#pragma once
#include "Matrix.hpp"

namespace OpenArabTools {
	enum OPENARABTOOLS_OBJ ChessboardStyle : uint8_t {
		CHESSBOARD_STYLE_WHITE_BLACK = 0,
		CHESSBOARD_STYLE_DEFAULT_WOOD
	};

	enum OPENARABTOOLS_OBJ PieceColor : uint8_t {
		CHESSBOARD_PIECE_NONE = 0,
		CHESSBOARD_PIECE_WHITE,
		CHESSBOARD_PIECE_BLACK
	};

	class OPENARABTOOLS_OBJ Chessboard {
	public:
		Chessboard() noexcept;
		Chessboard(const uint64_t aSizeX, const uint64_t aSizeY) noexcept;

		void showWindow() noexcept;
		void hideWindow() noexcept;

		void put(const uint64_t aColumn, const uint64_t aRow, PieceColor aPiece) noexcept;
		void remove(const uint64_t aColumn, const uint64_t aRow) noexcept;

		PieceColor get(const uint64_t aId) const noexcept;
		PieceColor get(const uint64_t aColumn, const uint64_t aRow) const noexcept;
		uint64_t getWidth() const noexcept;
		uint64_t getHeight() const noexcept;
		uint64_t getSize() const noexcept;

		//
		// OpenArabTools necessities
		//

		bool open() const noexcept;
		bool update() noexcept;
		void run() noexcept;

		//
		// OpenArabTools extensions
		//

		void showWindowAndRun() noexcept;
		bool sleep(const uint64_t aMs) noexcept;

		void applyChessboardStyle(const ChessboardStyle aCS) noexcept;
		void applyChessboardStyle(const LightColor& aLight, const LightColor& aDark) noexcept;

		~Chessboard() noexcept;
	private:
		Matrix mMatrix;
	};
}