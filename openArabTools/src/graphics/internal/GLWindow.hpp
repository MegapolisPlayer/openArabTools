#pragma once
#include "GLBaseImplementation.hpp"

template class OPENARABTOOLS_OBJ std::basic_string<char>;

namespace OpenArabTools {
	//Forward declaration
	class OPENARABTOOLS_OBJ Matrix;

	namespace Internal {
		//Forward declaration
		class OPENARABTOOLS_OBJ GLWindow;

		//Copies buffers (VBO, IBO) between 2 window classes
		OPENARABTOOLS_OBJ void BufferCopy(const GLWindow& aWindow1, GLWindow& aWindow2) noexcept;

		//Main Window Class - cannot be instantiated
		class OPENARABTOOLS_OBJ GLWindow {
			friend class OPENARABTOOLS_OBJ ::OpenArabTools::Matrix;
			friend OPENARABTOOLS_OBJ void BufferCopy(const GLWindow& aWindow1, GLWindow& aWindow2) noexcept;
		public:
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

			virtual void Resize(const uint64_t aWidth, const uint64_t aHeight) noexcept;
			uint64_t SizeX() const noexcept;
			uint64_t SizeY() const noexcept;

			void SetBackground(const double_t aAll) noexcept;
			void SetBackground(const double_t aRGB, const double_t aA) noexcept;
			void SetBackground(const double_t aR, const double_t aG, const double_t aB, const double_t aA) noexcept;

			virtual void BindShader() const noexcept = 0;
			void BindContext() const noexcept;

			void Process() noexcept;
			void Events() noexcept;

			bool IsWindowOpen() const noexcept;
			bool IsWindowHidden() const noexcept;

			bool operator~() const noexcept; //returns if window still open

			virtual void Reset() noexcept; //resets ONLY window, shaders specified in derived classes

			uint64_t FrameNo() const noexcept; //gets. no of frame
			void FrameNoReset() noexcept; //resets frame no

			virtual ~GLWindow() noexcept;

			//VARIABLES

			//VAO, VBO, IBO, per window (must be in OpenGL context)

			GLVertexArray glVAO;
			GLVertexBuffer glVBO;
			GLIndexBuffer glIBO;
		protected: //PRIVATE SECTION
			GLFWwindow* mWindow;
			uint64_t mWidth, mHeight;
			uint64_t mFrameNo;
			std::string mTitle;

			static uint64_t msDefaultWindowSize;

			static void SizeCallback(GLFWwindow* apWindow, const int aWidth, const int aHeight) noexcept;
			void HandleUserResize(const uint64_t aWidth, const uint64_t aHeight) noexcept;

			void CreateWindow() noexcept;

			virtual void ShadersInit() noexcept = 0;
			virtual void ShadersDestroy() noexcept = 0;
		};

		//Specializations (chlidren)

		//Outputs circles in output (for Matrix and derivatives)
		class OPENARABTOOLS_OBJ GLCircleWindow : public GLWindow {
		public:
			GLCircleWindow();
			GLCircleWindow(const uint64_t aWidth, const uint64_t aHeight) noexcept;
			GLCircleWindow(const GLCircleWindow& aOther) noexcept;
			GLCircleWindow(GLCircleWindow&& aOther) noexcept;
			GLCircleWindow& operator=(const GLCircleWindow& aOther) noexcept;
			GLCircleWindow& operator=(GLCircleWindow&& aOther) noexcept;

			virtual void Resize(const uint64_t aWidth, const uint64_t aHeight) noexcept override;
			virtual void Reset() noexcept override;
			virtual void BindShader() const noexcept override;

			//Internal radius - radius of empty space in middle of circle, almost never used
			void PrepareUniforms(const uint64_t aAmountCirclesX, const uint64_t aAmountCirclesY, const double_t aInternalRadius = 0.0) noexcept;



			//shaders, per window (must be in OpenGL context)
			//CS = Circle Shader, U = Uniform, S = SSBO
			GLHandle glCircleShader;

			//glCSUSize - 2 floats, size of circle boundary
			//glCSUResolution - 2 ints, resolution of window
			//glCSUInternalRadius - GLfloat, internal radius
			//glCSUExternalRadius - GLfloat, radius
			GLHandle glCSUSize, glCSUResolution, glCSUInternalRadius, glCSUExternalRadius;
		protected:
			virtual void ShadersInit() noexcept override;
			virtual void ShadersDestroy() noexcept override;
		};

		/*
		//Normal window, outputs same color without modification (for Canvas and derivatives)
		class OPENARABTOOLS_OBJ GLPassthroughWindow : public GLWindow {
		public:
			GLPassthroughWindow();
			GLPassthroughWindow(const uint64_t aWidth, const uint64_t aHeight) noexcept;
			GLPassthroughWindow(const GLCircleWindow& aOther) noexcept;
			GLPassthroughWindow(GLPassthroughWindow&& aOther) noexcept;
			GLPassthroughWindow& operator=(const GLPassthroughWindow& aOther) noexcept;
			GLPassthroughWindow& operator=(GLPassthroughWindow&& aOther) noexcept;

			//passthrough shader
			GLHandle glShader;
		protected:
			void ShadersInit() noexcept override;
			void ShadersDestroy() noexcept override;
		};
		*/
	}
}

