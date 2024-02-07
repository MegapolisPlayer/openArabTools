#pragma once
#include "internal/GLInterface.hpp"

namespace OpenArabTools {
	//Matrix creation helpers

	//Creates a single 1x1 matrix (a simple light)
	#define OPENARABTOOLS_MATRIX_SINGLE        1,1
	//Creates a vertical single-column matrix
	#define OPENARABTOOLS_MATRIX_VERTICAL(y)   1,y
	//Creates a horizontal single-row matrix
	#define OPENARABTOOLS_MATRIX_HORIZONTAL(x) x,1

	//Matrix class - the base of OpenArabTools graphics
	class OPENARABTOOLS_OBJ Matrix {
	public:
		//Constructor
		Matrix() noexcept;
		//Setup constructor
		Matrix(const U64 aSizeX, const U64 aSizeY) noexcept;
		//Copy constructor
		Matrix(const Matrix& aOther) noexcept;
		//Move constructor
		Matrix(Matrix&& aOther) noexcept;
		//Copy assignment
		Matrix& operator=(const Matrix& aOther) noexcept;
		//Move assignment
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

		//If size 1x1 -> turns light off, otherwise turns off checks the top-left
		void setOff() noexcept;

		void setOff(const U64 aId) noexcept;

		void setOff(const U64 aColumn, const U64 aRow) noexcept;

		//If size 1x1 -> turns light on, otherwise turns on the top-left
		void setOn() noexcept;

		void setOn(const U64 aId) noexcept;

		void setOn(const U64 aColumn, const U64 aRow) noexcept;

		void setOnOff(const bool aOnOff) noexcept;

		void setOnOff(const U64 aId, const bool aOnOff) noexcept;

		void setOnOff(const U64 aColumn, const U64 aRow, const bool aOnOff) noexcept;

		//
		// Getters
		//

		//If size 1x1 -> Returns background of light, otherwise returns from top-left
		LightColor getBackground() const noexcept;

		LightColor getBackground(const U64 aColumn, const U64 aRow) const noexcept;

		//If size 1x1 -> Returns color of light, otherwise returns from top-left
		LightColor getColor() const noexcept;

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

		// OPENARABTOOLS necessities

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

		//Shows the window and runs the matrix (blocks executions on thread until window closed) 
		void showWindowAndRun() noexcept;

		//Sets the matrix
		void set(const U64 aSizeX, const U64 aSizeY) noexcept;

		//Resets the matrix
		void reset() noexcept;

		//Change the amount of lights
		void resizeMatrix(const U64 aNewX, const U64 aNewY) noexcept;

		//Sleeps on this thread while still updating window, returns true if window stayed open (and false if window closed)
		//NOTE: invalidates Matrix if window closed
		bool sleep(const U64 aMs) noexcept;

		//Destructor
		~Matrix() noexcept;
	private:
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
	};
}