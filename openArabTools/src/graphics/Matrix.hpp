#pragma once
#include "internal/GLInterface.hpp"

namespace OpenArabTools {
	//LightColor predefined colors
	enum LightColorPredefined {
		LIGHTCOLOR_RED,
		LIGHTCOLOR_BLUE,
		//TODO: finish
	};

	//LightColor structure
	struct OPENARABTOOLS_OBJ LightColor {
		Dec R = 0.0, G = 0.0, B = 0.0;

		void RGB(const Dec aR, const Dec aG, const Dec aB) noexcept;

		void Darken();

		void Lighten();

		OPENARABTOOLS_EXTENSION(void RGB255(const U08 aR, const U08 aG, const U08 aB) noexcept);
	};

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

		OPENARABTOOLS_EXTENSION(void ResizeMatrix(const U64 aNewWidth, const U64 aNewHeight) noexcept);

		//Shows the window
		void ShowWindow() noexcept;
		//Hides the windows
		void HideWindow() noexcept;

		//Enables callback to Matrix
		void EnableInteraction(MatrixInteractionCallback aCallback) noexcept;

		//Disables callback to Matrix
		void DisableInteration() noexcept;

		//Transfers resources if we want to reuse
		OPENARABTOOLS_EXTENSION(void TransferResources(Matrix* aOther) noexcept);
		//Gets if resources transferred
		OPENARABTOOLS_EXTENSION(bool GetIfTransferedResources() const noexcept);

		~Matrix() noexcept;
	private:
		Internal::GLWindow mWindow;
		MatrixInteractionCallback mCallback;
		bool mResourcesTransferred;
	};
}