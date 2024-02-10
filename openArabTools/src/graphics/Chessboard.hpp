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
		Chessboard(const U64 aSizeX, const U64 aSizeY) noexcept;


		void showWindow() noexcept;
		void hideWindow() noexcept;

		void put(const U64 aColumn, const U64 aRow, PieceColor aPiece) noexcept;
		void remove(const U64 aColumn, const U64 aRow) noexcept;

		PieceColor get(const U64 aColumn, const U64 aRow) const noexcept;
		U64 getWidth() const noexcept;
		U64 getHeight() const noexcept;

		//
		// OPENARABTOOLS necessities
		//

		bool open() const noexcept;
		bool update() noexcept;
		void run() noexcept;

		//
		// OPENARABTOOLS extensions
		//


		void showWindowAndRun() noexcept;
		bool sleep(const U64 aMs) noexcept;

		void applyChessboardStyle(const ChessboardStyle aCS) noexcept;
		void applyChessboardStyle(const LightColor& aLight, const LightColor& aDark) noexcept;

		~Chessboard() noexcept;
	private:
		Matrix mMatrix;
		ChessboardStyle mCS;
	};
}