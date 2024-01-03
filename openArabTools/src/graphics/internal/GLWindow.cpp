#include "GLWindow.hpp"

//disable annoying "possible loss of data" warning
#pragma warning( disable : 4244 ) 

namespace OpenArabTools {
	namespace Internal {
		GLWindow::GLWindow() noexcept {
			Init();
			this->mWidth = 500;
			this->mHeight = 500;
			this->mWindow = glfwCreateWindow(500, 500, "OpenArabTools", NULL, NULL);
			glfwMakeContextCurrent(this->mWindow);
			glewInit();
			ShadersInit();
		}
		GLWindow::GLWindow(const U64 aWidth, const U64 aHeight) noexcept {
			Init();
			this->mWidth = aWidth;
			this->mHeight = aHeight;
			this->mWindow = glfwCreateWindow(this->mWidth, this->mHeight, "OpenArabTools", NULL, NULL);
			glfwMakeContextCurrent(this->mWindow);
			glewInit();
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
			glfwSetWindowSize(this->mWindow, aWidth, aHeight);
			glViewport(0, 0, aWidth, aHeight);
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
		}
		bool GLWindow::IsWindowOpen() noexcept {
			return !glfwWindowShouldClose(this->mWindow);
		}
		bool GLWindow::operator~() noexcept {
			return !glfwWindowShouldClose(this->mWindow);
		}
		GLFWwindow* GLWindow::GetWindow() noexcept {
			return this->mWindow;
		}

		void GLWindow::BindNormalShader() const noexcept {
			glUseProgram(this->NormalShader);
		}
		void GLWindow::BindCircleShader() const noexcept {
			glUseProgram(this->CircleShader);
		}

		void GLWindow::UnbindShaders() const noexcept {
			glUseProgram(0);
		}

		GLHandle GLWindow::GetNormalShader() noexcept {
			return this->NormalShader;
		}
		GLHandle GLWindow::GetCircleShader() noexcept {
			return this->CircleShader;
		}

		GLHandle GLWindow::GetNormalShaderResolutionUniform() noexcept {
			return this->NormalShader_ResolutionUniform;
		}
		GLHandle GLWindow::GetCircleShaderResolutionUniform() noexcept {
			return this->CircleShader_ResolutionUniform;
		}

		GLWindow::~GLWindow() noexcept {
			ShadersDestroy();
			glfwDestroyWindow(this->mWindow);
			Terminate();
		}

		// PRIVATE

		void GLWindow::ShadersInit() {
			this->NormalShader = Internal::MakeShader(Internal::VertexPassthroughSource, Internal::FragmentPassthroughSource);
			this->CircleShader = Internal::MakeShader(Internal::VertexPassthroughSource, Internal::FragmentCircleSource);
			this->NormalShader_ResolutionUniform = Internal::GetUniform(NormalShader, "Resolution");
			this->CircleShader_ResolutionUniform = Internal::GetUniform(CircleShader, "Resolution");
		}
		void GLWindow::ShadersDestroy() {
			glDeleteProgram(this->NormalShader);
			glDeleteProgram(this->CircleShader);
		}
	}
}