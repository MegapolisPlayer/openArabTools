#pragma once
#include "GLBatchRender.hpp"

namespace OpenArabTools {
	namespace Internal {
		//Main Window Class (for OpenGL)
		class OPENARABTOOLS_OBJ GLWindow {
		public:
			//Creates a new OpenGL Window
			GLWindow() noexcept;
			//Creates a new OpenGL Window, with parameters
			GLWindow(const U64 aWidth, const U64 aHeight) noexcept;

			//Shows the window
			void ShowWindow() noexcept;

			//Hides the window
			void HideWindow() noexcept;

			//Sets the title of the window
			void SetTitle(const char* aTitle) noexcept;

			//Resize the window
			void Resize(const U64 aWidth, const U64 aHeight) noexcept;

			//Sets new background
			void SetBackground(const Dec aAll) noexcept;
			//Sets new background
			void SetBackground(const Dec aRGB, const Dec aA) noexcept;
			//Sets new background
			void SetBackground(const Dec aR, const Dec aG, const Dec aB, const Dec aA) noexcept;

			//Processes window events
			void Process() noexcept;

			//Returns if window should be open
			bool IsWindowOpen() noexcept;

			//Operator ~, returns if window should be still open
			bool operator~() noexcept;

			//Gets the window handle
			GLFWwindow* GetWindow() noexcept;

			//Destructor
			~GLWindow() noexcept;
		private:
			GLFWwindow* mWindow;
			U64 mWidth, mHeight;
		};
	}
}

