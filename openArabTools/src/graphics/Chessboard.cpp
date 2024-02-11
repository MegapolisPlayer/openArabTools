#include "Chessboard.hpp"

namespace OpenArabTools {
	Chessboard::Chessboard() noexcept {
		this->mMatrix.set(8, 8);
		this->applyChessboardStyle(CHESSBOARD_STYLE_DEFAULT_WOOD);
	}
	Chessboard::Chessboard(const U64 aSizeX, const U64 aSizeY) noexcept {
		this->mMatrix.set(aSizeX, aSizeY);
		this->applyChessboardStyle(CHESSBOARD_STYLE_DEFAULT_WOOD);
	}

	void Chessboard::showWindow() noexcept {
		this->mMatrix.showWindow();
	}
	void Chessboard::hideWindow() noexcept {
		this->mMatrix.hideWindow();
	}

	void Chessboard::put(const U64 aColumn, const U64 aRow, PieceColor aPiece) noexcept {
		if (aPiece == CHESSBOARD_PIECE_NONE) this->remove(aColumn, aRow);

		/*
		switch (aPiece) {
		case CHESSBOARD_PIECE_WHITE: this->mMatrix.setColor(aColumn, aRow, ); break;
		case CHESSBOARD_PIECE_BLACK: break;
		default: break;
		}
		*/

		this->mMatrix.setOn(aColumn, aRow);
	}
	void Chessboard::remove(const U64 aColumn, const U64 aRow) noexcept {
		this->mMatrix.setOff(aColumn, aRow);
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
		return this->mMatrix.open();
	}
	bool Chessboard::update() noexcept {
		return this->mMatrix.update();
	}
	void Chessboard::run() noexcept {
		this->mMatrix.run();
	}

	void Chessboard::showWindowAndRun() noexcept {
		this->mMatrix.showWindowAndRun();
	}
	bool Chessboard::sleep(const U64 aMs) noexcept {
		return this->mMatrix.sleep(aMs);
	}

	void Chessboard::applyChessboardStyle(const ChessboardStyle aCS) noexcept {
		switch (aCS) {
		case(CHESSBOARD_STYLE_WHITE_BLACK): this->applyChessboardStyle(LIGHTCOLOR_CHESSBOARD_WHITE, LIGHTCOLOR_CHESSBOARD_BLACK); return;
		case(CHESSBOARD_STYLE_DEFAULT_WOOD): this->applyChessboardStyle(LIGHTCOLOR_CHESSBOARD_LIGHT, LIGHTCOLOR_CHESSBOARD_DARK); return;
		}
	}
	void Chessboard::applyChessboardStyle(const LightColor& aLight, const LightColor& aDark) noexcept {
		for (U64 i = 0; i < this->mMatrix.getSize(); i++) {
			switch (i % 2 == 0) {
			case(true): this->mMatrix.setBackground(aLight); break;
			case(false): this->mMatrix.setBackground(aDark); break;
			}
		}
	}

	Chessboard::~Chessboard() noexcept {}
}