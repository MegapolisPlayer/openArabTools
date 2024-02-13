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
		Matrix(const U64 aSizeX, const U64 aSizeY) noexcept;
		Matrix(const Matrix& aOther) noexcept;
		Matrix(Matrix&& aOther) noexcept;
		Matrix& operator=(const Matrix& aOther) noexcept;
		Matrix& operator=(Matrix&& aOther) noexcept;

		//Shows the window
		void showWindow() noexcept;
		//Hides the windows
		void hideWindow() noexcept;

		//
		// Setters
		//

		void setTitle(const std::string& aTitle) noexcept;

		void setBackground(const LightColor aColor) noexcept;

		void setBackground(const U64 aId, const LightColor& aColor) noexcept;

		void setBackground(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept;

		void setColor(const LightColor& aColor) noexcept;

		void setColor(const U64 aId, const LightColor& aColor) noexcept;

		void setColor(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept;

		void setOff() noexcept;
		void setOff(const U64 aId) noexcept;
		void setOff(const U64 aColumn, const U64 aRow) noexcept;
		void setOn() noexcept;
		void setOn(const U64 aId) noexcept;
		void setOn(const U64 aColumn, const U64 aRow) noexcept;
		void setOnOff(const bool aOnOff) noexcept;
		void setOnOff(const U64 aId, const bool aOnOff) noexcept;
		void setOnOff(const U64 aColumn, const U64 aRow, const bool aOnOff) noexcept;

		//
		// Getters
		//

		LightColor getBackground() const noexcept;
		LightColor getBackground(const U64 aId) const noexcept;
		LightColor getBackground(const U64 aColumn, const U64 aRow) const noexcept;

		LightColor getColor() const noexcept;
		LightColor getColor(const U64 aId) const noexcept;
		LightColor getColor(const U64 aColumn, const U64 aRow) const noexcept;

		std::string getTitle() const noexcept;
		U64 getWidth() const noexcept;
		U64 getHeight() const noexcept;
		U64 getSize() const noexcept;

		//If size 1x1 -> Returns if light off, otherwise checks the top-left
		bool isOff() const noexcept;
		bool isOff(const U64 aId) const noexcept;
		bool isOff(const U64 aColumn, const U64 aRow) const noexcept;

		//If size 1x1 -> Returns if light on, otherwise checks the top-left
		bool isOn() const noexcept;
		bool isOn(const U64 aId) const noexcept;
		bool isOn(const U64 aColumn, const U64 aRow) const noexcept;

		//
		// OPENARABTOOLS necessities
		//

		//Returns if window is open
		bool open() const noexcept;

		//Call this in a loop, returns if window still open
		bool update() noexcept;

		//Call this once, blocks execution until window closed!
		void run() noexcept;

		//
		// OPENARABTOOLS extensions
		//

		void setOffColor(const LightColor& aColor) noexcept;
		void setOffColor(const U64 aId, const LightColor& aColor) noexcept;
		void setOffColor(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept;
		
		void setColorAlpha(const float aAlpha) noexcept;
		void setColorAlpha(const U64 aId, const float aAlpha) noexcept;
		void setColorAlpha(const U64 aColumn, const U64 aRow, const float aAlpha) noexcept;
		void setOffColorAlpha(const float aAlpha) noexcept;
		void setOffColorAlpha(const U64 aId, const float aAlpha) noexcept;
		void setOffColorAlpha(const U64 aColumn, const U64 aRow, const float aAlpha) noexcept;
		void setBackgroundAlpha(const float aAlpha) noexcept;
		void setBackgroundAlpha(const U64 aId, const float aAlpha) noexcept;
		void setBackgroundAlpha(const U64 aColumn, const U64 aRow, const float aAlpha) noexcept;

		void showWindowAndRun() noexcept;

		void set(const U64 aSizeX, const U64 aSizeY) noexcept;
		void reset() noexcept;

		void resizeMatrix(const U64 aNewX, const U64 aNewY) noexcept;

		//Sleeps on this thread while still updating window, returns true if window stayed open (and false if window closed)
		//NOTE: invalidates Matrix if window closed
		bool sleep(const U64 aMs) noexcept;

		//Destructor
		~Matrix() noexcept;
	//private:
		U64 mSizeX, mSizeY;

		Internal::GLWindow mWindow;

		Internal::CircleColor* mColor;
		Internal::GLShaderBuffer<Internal::CircleColor> mColorBuf;
		int* mIsOn; //array if lights on/off
		Internal::GLShaderBuffer<int> mIsOnBuf;

		bool mInit;

		// PRIVATE FUNCTIONS
		
		void UploadColorToShader() noexcept;
		void UploadStateToShader() noexcept;

		void CheckRangeID(const U64 aId) noexcept;
		void CheckRangeCR(const U64 aCol, const U64 aRow) noexcept;
	};
}