#pragma once
#include "GLBaseImplementation.hpp"

template class OPENARABTOOLS_OBJ std::basic_string<char>;

namespace OpenArabTools {
	//Forward declaration
	class OPENARABTOOLS_OBJ Matrix;

	namespace Internal {

		//Main Window Class (for OpenGL)
		class OPENARABTOOLS_OBJ GLWindow {
		public:
			friend class OPENARABTOOLS_OBJ ::OpenArabTools::Matrix;

			GLWindow() noexcept; //default 500, 500 (X,Y)
			GLWindow(const U64 aWidth, const U64 aHeight) noexcept;
			GLWindow(const GLWindow& aOther) noexcept;
			GLWindow(GLWindow&& aOther) noexcept;
			GLWindow& operator=(const GLWindow& aOther) noexcept;
			GLWindow& operator=(GLWindow&& aOther) noexcept;

			// WINDOW MANAGEMENT

			void ShowWindow() noexcept;
			void HideWindow() noexcept;

			void SetTitle(const char* aTitle) noexcept;
			std::string GetTitle() const noexcept;

			void Resize(const U64 aWidth, const U64 aHeight) noexcept;
			U64 SizeX() const noexcept;
			U64 SizeY() const noexcept;

			void SetBackground(const Dec aAll) noexcept;
			void SetBackground(const Dec aRGB, const Dec aA) noexcept;
			void SetBackground(const Dec aR, const Dec aG, const Dec aB, const Dec aA) noexcept;

			//Internal radius - radius of empty space in middle of circle, almost never used, if debug mode true and DEBUG defined - just prints arrays
			void PrepareUniforms(U64 aAmountCirclesX, U64 aAmountCirclesY, Dec aInternalRadius = 0.0, bool aDebugMode = false) noexcept;

			void BindContext() noexcept;

			void Process() noexcept;

			bool IsWindowOpen() const noexcept;
			bool operator~() const noexcept; //returns if window still open

			void Destroy() noexcept;

			U64 FrameNo() const noexcept; //gets. no of frame
			void FrameNoReset() noexcept; //resets frame no

			~GLWindow() noexcept;

			//VARIABLES


			//VAO, VBO, IBO, per window (must be in OpenGL context)

			GLVertexArray glVAO;
			GLVertexBuffer glVBO;
			GLIndexBuffer glIBO;

			//shaders, per window (must be in OpenGL context)
			//CS = Circle Shader, U = Uniform, S = SSBO

			GLHandle glCircleShader;

			//glCSUSize - 2 floats, size of circle boundary
			//glCSUResolution - 2 ints, resolution of window
			//glCSUInternalRadius - float, internal radius
			//glCSUExternalRadius - float, radius

			GLHandle glCSUSize, glCSUResolution, glCSUInternalRadius, glCSUExternalRadius;

		private: //PRIVATE SECTION
			GLFWwindow* mWindow;
			U64 mWidth, mHeight;
			U64 mFrameNo;
			std::string mTitle;

			static void SizeCallback(GLFWwindow* aWindow, const int aWidth, const int aHeight) noexcept;
			void HandleResize(const U64 aWidth, const U64 aHeight) noexcept;
			void HandleUserResize(const U64 aWidth, const U64 aHeight) noexcept;

			void CreateWindow() noexcept;

			void ShadersInit() noexcept;
			void ShadersDestroy() noexcept;
		};
	}
}

