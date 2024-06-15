#include "Chessboard.hpp"

namespace OpenArabTools {
	Chessboard::Chessboard() noexcept {
		this->mMatrix.set(8, 8);
		this->applyChessboardStyle(CHESSBOARD_STYLE_DEFAULT_WOOD);
	}
	Chessboard::Chessboard(const uint64_t aSizeX, const uint64_t aSizeY) noexcept {
		this->mMatrix.set(aSizeX, aSizeY);
		this->applyChessboardStyle(CHESSBOARD_STYLE_DEFAULT_WOOD);
	}

	void Chessboard::showWindow() noexcept {
		this->mMatrix.showWindow();
	}
	void Chessboard::hideWindow() noexcept {
		this->mMatrix.hideWindow();
	}

	void Chessboard::put(const uint64_t aColumn, const uint64_t aRow, PieceColor aPiece) noexcept {
		if (aPiece == CHESSBOARD_PIECE_NONE) this->remove(aColumn, aRow);

		switch (aPiece) {
		case CHESSBOARD_PIECE_WHITE: this->mMatrix.setColor(aColumn, aRow, LIGHTCOLOR_WHITE); break;
		case CHESSBOARD_PIECE_BLACK: this->mMatrix.setColor(aColumn, aRow, LIGHTCOLOR_BLACK); break;
		default: break;
		}

		this->mMatrix.setOn(aColumn, aRow);
	}
	void Chessboard::remove(const uint64_t aColumn, const uint64_t aRow) noexcept {
		this->mMatrix.setOff(aColumn, aRow);
	}

	PieceColor Chessboard::get(const uint64_t aId) const noexcept {
		if (!this->mMatrix.isOn(aId))
			return CHESSBOARD_PIECE_NONE;

		if (this->mMatrix.getColor(aId) == LightColor(LIGHTCOLOR_WHITE))
			return CHESSBOARD_PIECE_WHITE;
		else
			return CHESSBOARD_PIECE_BLACK;
	}
	PieceColor Chessboard::get(const uint64_t aColumn, const uint64_t aRow) const noexcept {
		if (!this->mMatrix.isOn(aColumn, aRow))
			return CHESSBOARD_PIECE_NONE;

		if (this->mMatrix.getColor(aColumn, aRow) == LightColor(LIGHTCOLOR_WHITE))
			return CHESSBOARD_PIECE_WHITE;
		else
			return CHESSBOARD_PIECE_BLACK;
	}

	uint64_t Chessboard::getWidth() const noexcept {
		return this->mMatrix.getWidth();
	}
	uint64_t Chessboard::getHeight() const noexcept {
		return this->mMatrix.getHeight();
	}
	uint64_t Chessboard::getSize() const noexcept {
		return this->mMatrix.getSize();
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
	bool Chessboard::sleep(const uint64_t aMs) noexcept {
		return this->mMatrix.sleep(aMs);
	}

	void Chessboard::applyChessboardStyle(const ChessboardStyle aCS) noexcept {
		switch (aCS) {
		case(CHESSBOARD_STYLE_WHITE_BLACK): this->applyChessboardStyle(LIGHTCOLOR_CHESSBOARD_WHITE, LIGHTCOLOR_CHESSBOARD_BLACK); return;
		case(CHESSBOARD_STYLE_DEFAULT_WOOD): this->applyChessboardStyle(LIGHTCOLOR_CHESSBOARD_LIGHT, LIGHTCOLOR_CHESSBOARD_DARK); return;
		default: Error::warning("Invalid Chessboard style, no changes made."); return;
		}
	}
	void Chessboard::applyChessboardStyle(const LightColor& aLight, const LightColor& aDark) noexcept {
		for (uint64_t i = 0; i < this->mMatrix.getSize(); i++) {
			switch ((i + (i / this->mMatrix.getWidth())) % 2) {
				case(true): this->mMatrix.setBackground(i, aLight); break;
				case(false): this->mMatrix.setBackground(i, aDark); break;
			}
		}
	}

	Chessboard::~Chessboard() noexcept {}
}