#include "Matrix.hpp"

//TODO: finish matrix!!!!!!!!!

namespace OpenArabTools {
	Matrix::Matrix() noexcept {
	
	}
	Matrix::Matrix(const U64 aWidth, const U64 aHeight) noexcept {
	
	}

	void Matrix::showWindow() noexcept {
		this->mWindow.ShowWindow();
	}
	void Matrix::hideWindow() noexcept {
		this->mWindow.HideWindow();
	}

	void Matrix::setTitle(const std::string& aTitle) noexcept {
		this->mWindow.SetTitle(aTitle.c_str());
	}

	void Matrix::setBackground(const LightColor aColor) noexcept {
	
	}
	void Matrix::setBackground(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept {
	
	}
	void Matrix::setColor(const LightColor& color) noexcept {
	
	}
	void Matrix::setColor(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept {
	
	}

	void Matrix::setOff() noexcept {
		
	}
	void Matrix::setOff(const U64 aId) noexcept {
	
	}
	void Matrix::setOff(const U64 aColumn, const U64 aRow) noexcept {
	
	}
	void Matrix::setOn() noexcept {
	
	}
	void Matrix::setOn(const U64 aId) noexcept {
	
	}
	void Matrix::setOn(const U64 aColumn, const U64 aRow) noexcept {
	
	}
	void Matrix::setOnOff(const bool aOnOff) noexcept {
	
	}
	void Matrix::setOnOff(const U64 aId, const bool aOnOff) noexcept {
	
	}
	void Matrix::setOnOff(const U64 aColumn, const U64 aRow, const bool aOnOff) noexcept {
	
	}

	LightColor Matrix::getBackground() const noexcept {
		return this->mPanelBG;
	}
	LightColor Matrix::getBackground(const U64 aColumn, const U64 aRow) const noexcept {
		return { this->mColor[aColumn + (aRow * this->mSizeX)].BR, this->mColor[aColumn + (aRow * this->mSizeX)].BG, this->mColor[aColumn + (aRow * this->mSizeX)].BB };
	}
	LightColor Matrix::getColor() const noexcept {
		return this->mDefaultFG;
	}
	LightColor Matrix::getColor(const U64 aColumn, const U64 aRow) const noexcept {
		return { this->mColor[aColumn + (aRow * this->mSizeX)].FR, this->mColor[aColumn + (aRow * this->mSizeX)].FG, this->mColor[aColumn + (aRow * this->mSizeX)].FB };
	}
	std::string Matrix::getTitle() const noexcept {
		return this->mWindow.GetTitle();
	}
	U64 Matrix::getWidth() const noexcept {
		return this->mSizeX;
	}
	U64 Matrix::getHeight() const noexcept {
		return this->mSizeY;
	}
	U64 Matrix::getSize() const noexcept {
		return this->mSizeX * this->mSizeY;
	}

	bool Matrix::isOff() const noexcept {
		return !bool(this->mIsOn[0]);
	}
	bool Matrix::isOff(const U64 aId) const noexcept {
		return !bool(this->mIsOn[aId]);
	}
	bool Matrix::isOff(const U64 aColumn, const U64 aRow) const noexcept {
		return !bool(this->mIsOn[aColumn + (aRow * this->mSizeX)]);
	}
	bool Matrix::isOn() const noexcept {
		return bool(this->mIsOn[0]);
	}
	bool Matrix::isOn(const U64 aId) const noexcept {
		return bool(this->mIsOn[aId]);
	}
	bool Matrix::isOn(const U64 aColumn, const U64 aRow) const noexcept {
		return bool(this->mIsOn[aColumn + (aRow * 5)]);
	}

	void Matrix::resizeMatrix(const U64 aNewX, const U64 aNewY) noexcept {
		this->mSizeX = aNewX;
		this->mSizeY = aNewY;

		//TODO: realloc buffers
		//TODO: finish matrix class
	}

	//
	//openarabtools extensions
	//

	void Matrix::enableInteraction(MatrixInteractionCallback* aCallback) noexcept {

	}
	void Matrix::disableInteration() noexcept {

	}

	void Matrix::transferResources(Matrix* aOther) noexcept {
	
	}
	bool Matrix::getIfResourcesTransferred() const noexcept {
	
	}

	//
	//end of openarabtools extensions
	//

	Matrix::~Matrix() noexcept {
	
	}
}