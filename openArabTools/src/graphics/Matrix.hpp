#pragma once
#include "internal/GLInterface.hpp"

namespace OpenArabTools {
	//Matrix creation helpers

	//Creates a single 1x1 matrix (a simple light)
	#define OPENARABTOOLS_SINGLE        1,1
	//Creates a vertical single-column matrix
	#define OPENARABTOOLS_VERTICAL(y)   1,y
	//Creates a horizontal single-row matrix
	#define OPENARABTOOLS_HORIZONTAL(x) x,1

	//Matrix class
	class OPENARABTOOLS_OBJ Matrix {
	public:
		//Constructor
		Matrix() noexcept;
		//Setup constructor
		Matrix(const U64 aWidth, const U64 aHeight) noexcept;

		//Shows the window
		void showWindow() noexcept;
		//Hides the windows
		void hideWindow() noexcept;

		//Shows a basic example of the semaphore class
		static void main() noexcept;

		//
		// Setters
		//

		void setBackground(const LightColor aColor) noexcept;

		void setBackground(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept;

		void setColor(const LightColor& color) noexcept;

		void setColor(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept;

		void setOff() noexcept;

		bool setOff(const U64 aId) noexcept;

		bool setOff(const U64 aColumn, const U64 aRow) noexcept;

		void setOn() noexcept;

		bool setOn(const U64 aId) noexcept;

		bool setOn(const U64 aColumn, const U64 aRow) noexcept;

		void seOnOff(const bool aOnOff) noexcept;

		bool setOnOff(const U64 aId, const bool aOnOff) noexcept;

		bool setOnOff(const U64 aColumn, const U64 aRow, const bool aOnOff) noexcept;

		//
		// Getters
		//

		LightColor getBackground() const noexcept;

		LightColor getBackground(const U64 aColumn, const U64 aRow) const noexcept;

		LightColor getColor() const noexcept;

		LightColor getColor(const U64 aColumn, const U64 aRow) const noexcept;

		std::string getTitle() const noexcept;

		U64 getWidth() const noexcept;

		U64 getHeight() const noexcept;

		U64 getSize() const noexcept;

		bool isOff() const noexcept;

		bool isOff(const U64 aId) const noexcept;

		bool isOff(const U64 aColumn, const U64 aRow) const noexcept;

		bool isOn() const noexcept;

		bool isOn(const U64 aId) const noexcept;

		bool isOn(const U64 aColumn, const U64 aRow) const noexcept;

		//
		// OPENARABTOOLS extensions
		//

		void resizeMatrix(const U64 aNewWidth, const U64 aNewHeight) noexcept;

		//Enables callback to Matrix
		void enableInteraction(MatrixInteractionCallback aCallback) noexcept;
		//Disables callback to Matrix
		void disableInteration() noexcept;

		//Transfers resources if we want to reuse
		void transferResources(Matrix* aOther) noexcept;
		//Gets if resources transferred
		bool getIfResourcesTransferred() const noexcept;

		~Matrix() noexcept;
	private:
		U64 mSizeX, mSizeY;

		int* mIsOn; //array if lights on/off
		LightColor mPanelBG;

		Internal::GLWindow mWindow;
		Internal::GLShaderBuffer<int> mShaderBuf;

		bool mResourcesTransferred;

		MatrixInteractionCallback mCallback;
	};
}