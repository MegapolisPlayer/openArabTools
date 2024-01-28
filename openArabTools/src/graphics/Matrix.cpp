#include "Matrix.hpp"

namespace OpenArabTools {
	Matrix::Matrix() noexcept {
	
	}
	Matrix::Matrix(const U64 aWidth, const U64 aHeight) noexcept {
	
	}

	void Matrix::showWindow() noexcept {}
	void Matrix::hideWindow() noexcept {}

	void Matrix::setTitle(const std::string& aTitle) noexcept {}

	void Matrix::setBackground(const LightColor aColor) noexcept {}
	void Matrix::setBackground(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept {}
	void Matrix::setColor(const LightColor& color) noexcept {}
	void Matrix::setColor(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept {}

	void Matrix::setOff() noexcept {}
	void Matrix::setOff(const U64 aId) noexcept {}
	void Matrix::setOff(const U64 aColumn, const U64 aRow) noexcept {}
	void Matrix::setOn() noexcept {}
	void Matrix::setOn(const U64 aId) noexcept {}
	void Matrix::setOn(const U64 aColumn, const U64 aRow) noexcept {}
	void Matrix::setOnOff(const bool aOnOff) noexcept {}
	void Matrix::setOnOff(const U64 aId, const bool aOnOff) noexcept {}
	void Matrix::setOnOff(const U64 aColumn, const U64 aRow, const bool aOnOff) noexcept {}

	LightColor Matrix::getBackground() const noexcept {}
	LightColor Matrix::getBackground(const U64 aColumn, const U64 aRow) const noexcept {}
	LightColor Matrix::getColor() const noexcept {}
	LightColor Matrix::getColor(const U64 aColumn, const U64 aRow) const noexcept {}
	std::string Matrix::getTitle() const noexcept {}
	U64 Matrix::getWidth() const noexcept {}
	U64 Matrix::getHeight() const noexcept {}
	U64 Matrix::getSize() const noexcept {}

	bool Matrix::isOff() const noexcept {}
	bool Matrix::isOff(const U64 aId) const noexcept {}
	bool Matrix::isOff(const U64 aColumn, const U64 aRow) const noexcept {}
	bool Matrix::isOn() const noexcept {}
	bool Matrix::isOn(const U64 aId) const noexcept {}
	bool Matrix::isOn(const U64 aColumn, const U64 aRow) const noexcept { }

	void Matrix::resizeMatrix(const U64 aNewWidth, const U64 aNewHeight) noexcept {}

	void Matrix::enableInteraction(MatrixInteractionCallback aCallback) noexcept {}
	void Matrix::disableInteration() noexcept {}

	void Matrix::transferResources(Matrix* aOther) noexcept {}
	bool Matrix::getIfResourcesTransferred() const noexcept {}

	Matrix::~Matrix() noexcept {}
}