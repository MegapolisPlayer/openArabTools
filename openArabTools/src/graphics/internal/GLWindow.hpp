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
			GLWindow(const uint64_t aWidth, const uint64_t aHeight) noexcept;
			GLWindow(const GLWindow& aOther) noexcept;
			GLWindow(GLWindow&& aOther) noexcept;
			GLWindow& operator=(const GLWindow& aOther) noexcept;
			GLWindow& operator=(GLWindow&& aOther) noexcept;

			// WINDOW MANAGEMENT

			void ShowWindow() noexcept;
			void HideWindow() noexcept;

			void SetTitle(const char* arTitle) noexcept;
			std::string GetTitle() const noexcept;

			void Resize(const uint64_t aWidth, const uint64_t aHeight) noexcept;
			uint64_t SizeX() const noexcept;
			uint64_t SizeY() const noexcept;

			void SetBackground(const double_t aAll) noexcept;
			void SetBackground(const double_t aRGB, const double_t aA) noexcept;
			void SetBackground(const double_t aR, const double_t aG, const double_t aB, const double_t aA) noexcept;

			//Internal radius - radius of empty space in middle of circle, almost never used
			void PrepareUniforms(const uint64_t aAmountCirclesX, const uint64_t aAmountCirclesY, const double_t aInternalRadius = 0.0) noexcept;

			void BindContext() noexcept;

			void Process() noexcept;
			void Events() noexcept;

			bool IsWindowOpen() const noexcept;
			bool operator~() const noexcept; //returns if window still open

			void Reset() noexcept;

			uint64_t FrameNo() const noexcept; //gets. no of frame
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
			uint64_t mWidth, mHeight;
			uint64_t mFrameNo;
			std::string mTitle;

			static uint64_t msDefaultWindowSize;

			static void SizeCallback(GLFWwindow* apWindow, const int aWidth, const int aHeight) noexcept;
			void HandleResize(const uint64_t aWidth, const uint64_t aHeight) noexcept;
			void HandleUserResize(const uint64_t aWidth, const uint64_t aHeight) noexcept;

			void CreateWindow() noexcept;

			void ShadersInit() noexcept;
			void ShadersDestroy() noexcept;
		};
	}
}

