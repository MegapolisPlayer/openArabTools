#include "GLWindow.hpp"

//disable annoying "possible loss of data" warning
#pragma warning( disable : 4244 ) 

namespace OpenArabTools {
	namespace Internal {
		GLWindow::GLWindow() noexcept : mWidth(500), mHeight(500), mFrameNo(0), mTitle() {
			init();

			this->mWindow = glfwCreateWindow(500, 500, "OpenArabTools", NULL, NULL);
			glfwSetWindowUserPointer(this->mWindow, this);
			glfwSetWindowSizeCallback(this->mWindow, SizeCallback);
			glfwMakeContextCurrent(this->mWindow);
			glewInit();

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			this->glVAO.Bind();
			ShadersInit();
		}
		GLWindow::GLWindow(const U64 aWidth, const U64 aHeight) noexcept : mWidth(aWidth), mHeight(aHeight), mFrameNo(0), mTitle() {
			init();

			this->mWindow = glfwCreateWindow(this->mWidth, this->mHeight, "OpenArabTools", NULL, NULL);
			glfwSetWindowUserPointer(this->mWindow, this);
			glfwSetWindowSizeCallback(this->mWindow, SizeCallback);
			glfwMakeContextCurrent(this->mWindow);
			glewInit();

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			this->glVAO.Bind();
			ShadersInit();
		}
		void GLWindow::ShowWindow() noexcept {
			glfwShowWindow(this->mWindow);
		}
		void GLWindow::HideWindow() noexcept {
			glfwHideWindow(this->mWindow);
		}
		void GLWindow::SetTitle(const char* aTitle) noexcept {
			this->mTitle = aTitle;
			glfwSetWindowTitle(this->mWindow, this->mTitle.c_str());
		}
		void GLWindow::Resize(const U64 aWidth, const U64 aHeight) noexcept {
			this->HandleResize(aWidth, aHeight);
			glfwSetWindowSize(this->mWindow, this->mWidth, this->mHeight);
		}
		U64 GLWindow::SizeX() const noexcept {
			return this->mWidth;
		}
		U64 GLWindow::SizeY() const noexcept {
			return this->mHeight;
		}
		void GLWindow::SetBackground(const Dec aAll) noexcept {
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(aAll, aAll, aAll, aAll);
		}
		void GLWindow::SetBackground(const Dec aRGB, const Dec aA) noexcept {
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(aRGB, aRGB, aRGB, aA);
		}
		void GLWindow::SetBackground(const Dec aR, const Dec aG, const Dec aB, const Dec aA) noexcept {
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(aR, aG, aB, aA);
		}
		void GLWindow::PrepareUniforms(U64 aAmountCirclesX, U64 aAmountCirclesY, Dec aInternalRadius, bool aDebugMode) noexcept {
			glUseProgram(this->glCircleShader);
			glUniform2f(this->glCSUResolution, this->mWidth, this->mHeight);
			glUniform1f(this->glCSUInternalRadius, aInternalRadius);
			//pick half of SMALLER size = more circles
			glUniform1f(
				this->glCSUExternalRadius, 
				(aAmountCirclesX > aAmountCirclesY) ? (2.0 / aAmountCirclesX / 2.0) : (2.0 / aAmountCirclesY / 2.0)
			);
			glUniform2f(this->glCSUSize, 2.0 / aAmountCirclesX, 2.0 / aAmountCirclesY);
		}
		void GLWindow::Process() noexcept {
			glfwSwapBuffers(this->mWindow);
			glfwPollEvents();
			this->mFrameNo++;
		}
		bool GLWindow::IsWindowOpen() const noexcept {
			return !glfwWindowShouldClose(this->mWindow);
		}
		bool GLWindow::operator~() const noexcept {
			return !glfwWindowShouldClose(this->mWindow);
		}
		void GLWindow::Destroy() noexcept {
			if (this->mWindow == NULL) return;

			this->Process();
			glfwDestroyWindow(this->mWindow);
			ShadersDestroy();
			this->mWindow = NULL;
			terminate();
		}
		U64 GLWindow::FrameNo() const noexcept {
			return this->mFrameNo;
		}
		void GLWindow::FrameNoReset() noexcept {
			this->mFrameNo = 0;
		}
		GLWindow::~GLWindow() noexcept {
			this->Destroy();
		}

		// PRIVATE

		void GLWindow::SizeCallback(GLFWwindow* aWindow, const int aWidth, const int aHeight) noexcept {
			((GLWindow*)glfwGetWindowUserPointer(aWindow))->HandleResize(aWidth, aHeight);
		}
		void GLWindow::HandleResize(const U64 aWidth, const U64 aHeight) noexcept {
			this->mWidth = aWidth;
			this->mHeight = aHeight;
			glViewport(0, 0, this->mWidth, this->mHeight);
			glUniform2f(this->glCSUResolution, this->mWidth, this->mHeight);
		}

		void GLWindow::ShadersInit() noexcept {
			this->glCircleShader = Internal::MakeShader(Internal::VertexCircleSource, Internal::FragmentCircleSource);
			this->glCSUSize = glGetUniformLocation(this->glCircleShader, "Size");
			this->glCSUResolution = glGetUniformLocation(this->glCircleShader, "WindowResolution");
			this->glCSUInternalRadius = glGetUniformLocation(this->glCircleShader, "IRadius");
			this->glCSUExternalRadius = glGetUniformLocation(this->glCircleShader, "ERadius");
		}
		void GLWindow::ShadersDestroy() noexcept {
			glDeleteProgram(this->glCircleShader);
		}
	}
}