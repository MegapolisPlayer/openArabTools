#include "Chessboard.hpp"

namespace OpenArabTools {
	Chessboard::Chessboard() noexcept {
	
	}
	Chessboard::Chessboard(const U64 aSizeX, const U64 aSizeY) noexcept {
	
	}

	void Chessboard::showWindow() noexcept {
		this->mMatrix.showWindow();
	}
	void Chessboard::hideWindow() noexcept {
		this->mMatrix.hideWindow();
	}

	void Chessboard::put(const U64 aColumn, const U64 aRow, PieceColor aPiece) noexcept {

	}
	void Chessboard::remove(const U64 aColumn, const U64 aRow) noexcept {

	}

	PieceColor Chessboard::get(const U64 aColumn, const U64 aRow) const noexcept {
		return CHESSBOARD_PIECE_NONE;
	}
	U64 Chessboard::getWidth() const noexcept {
		return this->mMatrix.getWidth();
	}
	U64 Chessboard::getHeight() const noexcept {
		return this->mMatrix.getHeight();
	}

	bool Chessboard::open() const noexcept {
		return false;
	}
	bool Chessboard::update() noexcept {
		return false;
	}
	void Chessboard::run() noexcept {

	}

	void Chessboard::showWindowAndRun() noexcept {
	
	}
	void Chessboard::reset() noexcept {

	}
	bool Chessboard::sleep(const U64 aMs) noexcept {
		return this->mMatrix.sleep(aMs);
	}

	Chessboard::~Chessboard() noexcept {
	
	}
}