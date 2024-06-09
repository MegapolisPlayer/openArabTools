#pragma once
#include "internal/GLInterface.hpp"

namespace OpenArabTools {
	//Creates a single 1x1 matrix (a simple light)
	#define OPENARABTOOLS_MATRIX_SINGLE        1,1
	//Creates a vertical single-column matrix
	#define OPENARABTOOLS_MATRIX_VERTICAL(y)   1,y
	//Creates a horizontal single-row matrix
	#define OPENARABTOOLS_MATRIX_HORIZONTAL(x) x,1

	//Matrix class - the base of OpenArabTools graphics
	class OPENARABTOOLS_OBJ Matrix {
	public:
		Matrix() noexcept;
		Matrix(const uint64_t aSizeX, const uint64_t aSizeY) noexcept;
		Matrix(const Matrix& aOther) noexcept;
		Matrix(Matrix&& aOther) noexcept;
		Matrix& operator=(const Matrix& aOther) noexcept;
		Matrix& operator=(Matrix&& aOther) noexcept;

		void showWindow() noexcept;
		void hideWindow() noexcept;

		//
		// Setters
		//

		void setTitle(const std::string& aTitle) noexcept;

		void setBackground(const LightColor aColor) noexcept;
		void setBackground(const uint64_t aId, const LightColor& aColor) noexcept;
		void setBackground(const uint64_t aColumn, const uint64_t aRow, const LightColor& aColor) noexcept;

		void setColor(const LightColor& aColor) noexcept;
		void setColor(const uint64_t aId, const LightColor& aColor) noexcept;
		void setColor(const uint64_t aColumn, const uint64_t aRow, const LightColor& aColor) noexcept;

		void setOff() noexcept;
		void setOff(const uint64_t aId) noexcept;
		void setOff(const uint64_t aColumn, const uint64_t aRow) noexcept;
		void setOn() noexcept;
		void setOn(const uint64_t aId) noexcept;
		void setOn(const uint64_t aColumn, const uint64_t aRow) noexcept;
		void setOnOff(const bool aOnOff) noexcept;
		void setOnOff(const uint64_t aId, const bool aOnOff) noexcept;
		void setOnOff(const uint64_t aColumn, const uint64_t aRow, const bool aOnOff) noexcept;

		//
		// Getters
		//

		LightColor getBackground() const noexcept;
		LightColor getBackground(const uint64_t aId) const noexcept;
		LightColor getBackground(const uint64_t aColumn, const uint64_t aRow) const noexcept;

		LightColor getColor() const noexcept;
		LightColor getColor(const uint64_t aId) const noexcept;
		LightColor getColor(const uint64_t aColumn, const uint64_t aRow) const noexcept;

		std::string getTitle() const noexcept;
		uint64_t getWidth() const noexcept;
		uint64_t getHeight() const noexcept;
		uint64_t getSize() const noexcept;

		//If size 1x1 -> Returns if light off, otherwise checks the top-left
		bool isOff() const noexcept;
		bool isOff(const uint64_t aId) const noexcept;
		bool isOff(const uint64_t aColumn, const uint64_t aRow) const noexcept;

		//If size 1x1 -> Returns if light on, otherwise checks the top-left
		bool isOn() const noexcept;
		bool isOn(const uint64_t aId) const noexcept;
		bool isOn(const uint64_t aColumn, const uint64_t aRow) const noexcept;

		//
		// OpenArabTools necessities
		//

		//Returns if window is open
		bool open() const noexcept;
		//Call this in a loop, returns if window still open
		bool update() noexcept;
		//Call this once, blocks execution until window closed!
		void run() noexcept;

		//
		// OpenArabTools extensions
		//

		void setOffColor(const LightColor& aColor) noexcept;
		void setOffColor(const uint64_t aId, const LightColor& aColor) noexcept;
		void setOffColor(const uint64_t aColumn, const uint64_t aRow, const LightColor& aColor) noexcept;
		
		void setColorAlpha(const float aAlpha) noexcept;
		void setColorAlpha(const uint64_t aId, const float aAlpha) noexcept;
		void setColorAlpha(const uint64_t aColumn, const uint64_t aRow, const float aAlpha) noexcept;
		void setOffColorAlpha(const float aAlpha) noexcept;
		void setOffColorAlpha(const uint64_t aId, const float aAlpha) noexcept;
		void setOffColorAlpha(const uint64_t aColumn, const uint64_t aRow, const float aAlpha) noexcept;
		void setBackgroundAlpha(const float aAlpha) noexcept;
		void setBackgroundAlpha(const uint64_t aId, const float aAlpha) noexcept;
		void setBackgroundAlpha(const uint64_t aColumn, const uint64_t aRow, const float aAlpha) noexcept;

		void showWindowAndRun() noexcept;

		void set(const uint64_t aSizeX, const uint64_t aSizeY) noexcept;
		void reset() noexcept;

		void resizeMatrix(const uint64_t aNewX, const uint64_t aNewY) noexcept;

		//Sleeps on this thread while still updating window, returns true if window stayed open (and false if window closed)
		//NOTE: invalidates Matrix if window closed
		bool sleep(const uint64_t aMs) noexcept;

		//Destructor
		~Matrix() noexcept;
	//private:
		uint64_t mSizeX, mSizeY;

		Internal::GLCircleWindow mWindow;

		Internal::CircleColor* mrColor; //array of lights color
		Internal::GLShaderBuffer<Internal::CircleColor> mColorBuf;
		int* mrIsOn; //array if lights on/off
		Internal::GLShaderBuffer<int> mIsOnBuf;

		bool mInit;

		// PRIVATE FUNCTIONS
		
		void UploadColorToShader() noexcept;
		void UploadStateToShader() noexcept;

		void CheckRangeID(const uint64_t aId) noexcept;
		void CheckRangeCR(const uint64_t aCol, const uint64_t aRow) noexcept;
	};
}