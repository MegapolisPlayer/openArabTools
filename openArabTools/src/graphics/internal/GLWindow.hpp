#pragma once
#include "GLBatchRender.hpp"

namespace OpenArabTools {
	namespace Internal {
		//Main Window Class (for OpenGL)
		class OPENARABTOOLS_OBJ GLWindow {
		public:
			GLWindow() noexcept; //default 500, 500 (X,Y)
			GLWindow(const U64 aWidth, const U64 aHeight) noexcept;

			// WINDOW MANAGEMENT

			void ShowWindow() noexcept;
			void HideWindow() noexcept;

			void SetTitle(const char* aTitle) noexcept;

			void Resize(const U64 aWidth, const U64 aHeight) noexcept;
			U64 SizeX() const noexcept;
			U64 SizeY() const noexcept;

			void SetBackground(const Dec aAll) noexcept;
			void SetBackground(const Dec aRGB, const Dec aA) noexcept;
			void SetBackground(const Dec aR, const Dec aG, const Dec aB, const Dec aA) noexcept;

			void Process() noexcept;

			bool IsWindowOpen() const noexcept;
			bool operator~() const noexcept; //returns if window still open

			U64 FrameNo() const noexcept; //gets. no of frame
			void FrameNoReset() noexcept; //resets frame no

			~GLWindow() noexcept;

			//VARIABLES

			//VAO, per window (must be in OpenGL context)

			GLHandle glVAO;

			//shaders, per window (must be in OpenGL context)
			//NS = Normal/Passthrough Shader, CS = Circle Shader, U = Uniform

			GLHandle glNormalShader, glCircleShader;
			GLHandle glCSUSize, glCSUResolution, glCSUInternalRadius, glCSUExternalRadius;

		private: //PRIVATE SECTION
			GLFWwindow* mWindow;
			U64 mWidth, mHeight;
			U64 mFrameNo;

			void ShadersInit();
			void ShadersDestroy();
		};
	}
}

