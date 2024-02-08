#pragma once
#include "Matrix.hpp"

namespace OpenArabTools {
	enum OPENARABTOOLS_OBJ PieceColor : uint8_t {
		CHESSBOARD_PIECE_NONE = 0,
		CHESSBOARD_PIECE_WHITE,
		CHESSBOARD_PIECE_BLACK
	};

	class OPENARABTOOLS_OBJ Chessboard {
	public:
		Chessboard() noexcept;

		void showWindow() noexcept;
		void hideWindow() noexcept;

		//Puts a piece onto the chessboard. (if CHESSBOARD_PIECE_NONE set - removes the piece)
		void put(const U64 aColumn, const U64 aRow, PieceColor aPiece) noexcept;

		void remove(const U64 aColumn, const U64 aRow) noexcept;

		PieceColor get() const noexcept;
		U64 getHeight() const noexcept;
		U64 getWidth() const noexcept;

		~Chessboard() noexcept;
	private:
		Matrix mMatrix;
	};
}