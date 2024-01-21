#include "GLWindow.hpp"

//disable annoying "possible loss of data" warning
#pragma warning( disable : 4244 ) 

namespace OpenArabTools {
	namespace Internal {
		GLWindow::GLWindow() noexcept : mWidth(500), mHeight(500), mFrameNo(0) {
			init();

			this->mWindow = glfwCreateWindow(500, 500, "OpenArabTools", NULL, NULL);
			glfwMakeContextCurrent(this->mWindow);
			glewInit();

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glGenVertexArrays(1, &this->glVAO);
			glBindVertexArray(this->glVAO);
			ShadersInit();
		}
		GLWindow::GLWindow(const U64 aWidth, const U64 aHeight) noexcept : mWidth(aWidth), mHeight(aHeight), mFrameNo(0) {
			init();

			this->mWindow = glfwCreateWindow(this->mWidth, this->mHeight, "OpenArabTools", NULL, NULL);
			glfwMakeContextCurrent(this->mWindow);
			glewInit();

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glGenVertexArrays(1, &this->glVAO);
			glBindVertexArray(this->glVAO);
			ShadersInit();
		}
		void GLWindow::ShowWindow() noexcept {
			glfwShowWindow(this->mWindow);
		}
		void GLWindow::HideWindow() noexcept {
			glfwHideWindow(this->mWindow);
		}
		void GLWindow::SetTitle(const char* aTitle) noexcept {
			glfwSetWindowTitle(this->mWindow, aTitle);
		}
		void GLWindow::Resize(const U64 aWidth, const U64 aHeight) noexcept {
			this->mWidth = aWidth;
			this->mHeight = aHeight;
			glfwSetWindowSize(this->mWindow, this->mWidth, this->mHeight);
			glViewport(0, 0, this->mWidth, this->mHeight);
			glUniform2f(this->glCSUResolution, this->mWidth, this->mHeight);
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
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
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
		U64 GLWindow::FrameNo() const noexcept {
			return this->mFrameNo;
		}
		void GLWindow::FrameNoReset() noexcept {
			this->mFrameNo = 0;
		}
		GLWindow::~GLWindow() noexcept {
			glDeleteVertexArrays(1, &this->glVAO);
			ShadersDestroy();
			glfwDestroyWindow(this->mWindow);
			terminate();
		}

		// PRIVATE

		void GLWindow::ShadersInit() {
			this->glNormalShader = Internal::MakeShader(Internal::VertexBackgroundSource, Internal::FragmentBackgroundSource);
			this->glCircleShader = Internal::MakeShader(Internal::VertexCircleSource, Internal::FragmentCircleSource);
			this->glCSUSize = glGetUniformLocation(this->glCircleShader, "Size");
			this->glCSUResolution = glGetUniformLocation(this->glCircleShader, "WindowResolution");
			this->glCSUInternalRadius = glGetUniformLocation(this->glCircleShader, "IRadius");
			this->glCSUExternalRadius = glGetUniformLocation(this->glCircleShader, "ERadius");
		}
		void GLWindow::ShadersDestroy() {
			glDeleteProgram(this->glNormalShader);
			glDeleteProgram(this->glCircleShader);
		}
	}
}