#pragma once
#include "internal/GLInterface.hpp"

namespace OpenArabTools {
	//Matrix creation helpers

	//Creates a single 1x1 matrix
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

		void setBackground(LightColor aColor);

		void setBackground(U64 aColumn, U64 aRow, LightColor aColor);

		void setColor(LightColor color);

		void setColor(U64 aColumn, U64 aRow, LightColor aColor);

		//
		// Getters
		//



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
		Internal::GLWindow mWindow;
		MatrixInteractionCallback mCallback;
		bool mResourcesTransferred;
	};
}