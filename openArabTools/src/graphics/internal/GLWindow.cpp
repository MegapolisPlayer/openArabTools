#include "GLWindow.hpp"

//disable annoying "possible loss of data" warning
#pragma warning( disable : 4244 ) 

//same as normal ArabTools

namespace OpenArabTools {
	namespace Internal {
		uint64_t GLWindow::msDefaultWindowSize = 650;

		GLWindow::GLWindow() noexcept 
		: mWidth(msDefaultWindowSize), mHeight(msDefaultWindowSize), mFrameNo(0), mTitle("openArabTools")
		{ this->CreateWindow(); }

		GLWindow::GLWindow(const uint64_t aWidth, const uint64_t aHeight) noexcept
		: mWidth(aWidth), mHeight(aHeight), mFrameNo(0), mTitle("openArabTools")
		{ this->CreateWindow(); }

		GLWindow::GLWindow(const GLWindow& aOther) noexcept {
			if (&aOther == this) {
				Error::error("Self-assignment in GLWindow detected."); return;
			}

			this->mWidth = aOther.mWidth;
			this->mHeight = aOther.mHeight;
			this->mFrameNo = 0;
			this->mTitle = aOther.mTitle;
			this->CreateWindow();
		}
		GLWindow::GLWindow(GLWindow&& aOther) noexcept {
			if (&aOther == this) {
				Error::error("Self-assignment in GLWindow detected."); return;
			}

			this->mWidth = aOther.mWidth;
			this->mHeight = aOther.mHeight;
			this->mFrameNo = aOther.mFrameNo;
			this->mTitle = aOther.mTitle;

			this->mWindow = aOther.mWindow;
			aOther.mWindow = nullptr;

			this->glVAO = aOther.glVAO;
			this->glVBO = aOther.glVBO;
			this->glIBO = aOther.glIBO;
			this->glCircleShader = aOther.glCircleShader;
			this->glCSUSize = aOther.glCSUSize;
			this->glCSUResolution = aOther.glCSUResolution;
			this->glCSUInternalRadius = aOther.glCSUInternalRadius;
			this->glCSUExternalRadius = aOther.glCSUExternalRadius;
			this->glCircleShader = aOther.glCircleShader;
		}
		GLWindow& GLWindow::operator=(const GLWindow& aOther) noexcept {
			if (&aOther == this) {
				Error::error("Self-assignment in GLWindow detected."); return *this;
			}

			this->Reset();

			this->mWidth = aOther.mWidth;
			this->mHeight = aOther.mHeight;
			this->mFrameNo = 0;
			this->mTitle = aOther.mTitle;
			this->CreateWindow();

			return *this;
		}
		GLWindow& GLWindow::operator=(GLWindow&& aOther) noexcept {
			if (&aOther == this) {
				Error::error("Self-assignment in GLWindow detected."); return *this;
			}

			this->Reset();

			this->mWidth = aOther.mWidth;
			this->mHeight = aOther.mHeight;
			this->mFrameNo = aOther.mFrameNo;
			this->mTitle = aOther.mTitle;

			this->mWindow = aOther.mWindow;
			aOther.mWindow = nullptr;

			this->glVAO = aOther.glVAO;
			this->glVBO = aOther.glVBO;
			this->glIBO = aOther.glIBO;
			this->glCircleShader = aOther.glCircleShader;
			this->glCSUSize = aOther.glCSUSize;
			this->glCSUResolution = aOther.glCSUResolution;
			this->glCSUInternalRadius = aOther.glCSUInternalRadius;
			this->glCSUExternalRadius = aOther.glCSUExternalRadius;
			this->glCircleShader = aOther.glCircleShader;

			return *this;
		}

		void GLWindow::ShowWindow() noexcept {
			glfwShowWindow(this->mWindow);
		}
		void GLWindow::HideWindow() noexcept {
			glfwHideWindow(this->mWindow);
		}
		void GLWindow::SetTitle(const char* arTitle) noexcept {
			this->mTitle = arTitle;
			glfwSetWindowTitle(this->mWindow, this->mTitle.c_str());
		}
		std::string GLWindow::GetTitle() const noexcept {
			return this->mTitle;
		}
		void GLWindow::Resize(const uint64_t aWidth, const uint64_t aHeight) noexcept {
#ifdef OPENARABTOOLS_PRINT_DEBUG_INFO
			Error::warning("System window resize.");
#endif
			this->mWidth = aWidth;
			this->mHeight = aHeight;
			glViewport(0, 0, this->mWidth, this->mHeight);
			glUniform2f(this->glCSUResolution, this->mWidth, this->mHeight);
			glfwSetWindowSize(this->mWindow, this->mWidth, this->mHeight); //doesnt call callback!
		}
		uint64_t GLWindow::SizeX() const noexcept {
			return this->mWidth;
		}
		uint64_t GLWindow::SizeY() const noexcept {
			return this->mHeight;
		}
		void GLWindow::SetBackground(const double_t aAll) noexcept {
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(aAll, aAll, aAll, aAll);
		}
		void GLWindow::SetBackground(const double_t aRGB, const double_t aA) noexcept {
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(aRGB, aRGB, aRGB, aA);
		}
		void GLWindow::SetBackground(const double_t aR, const double_t aG, const double_t aB, const double_t aA) noexcept {
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(aR, aG, aB, aA);
		}
		void GLWindow::PrepareUniforms(const uint64_t aAmountCirclesX, const uint64_t aAmountCirclesY, const double_t aInternalRadius) noexcept {
			this->glVAO.Bind();
			this->glIBO.Bind();

			glUseProgram(this->glCircleShader);
			glUniform2f(this->glCSUResolution, this->mWidth, this->mHeight);
			glUniform1f(this->glCSUInternalRadius, aInternalRadius);
			glUniform1f(
				this->glCSUExternalRadius,
				1.0 / aAmountCirclesX
			);
			glUniform2f(this->glCSUSize, 2.0 / aAmountCirclesX, 2.0 / aAmountCirclesY);
		}
		void GLWindow::BindContext() noexcept {
			glfwMakeContextCurrent(this->mWindow);
		}
		void GLWindow::Process() noexcept {
			glfwSwapBuffers(this->mWindow);
			glfwPollEvents();
			this->mFrameNo++;
			glClear(GL_COLOR_BUFFER_BIT);
#ifdef _DEBUG
			//if debug: set background to purple (noticable if something wrong)
			glClearColor(0.7f, 0.0f, 0.7f, 1.0f);
#endif
		}
		void GLWindow::Events() noexcept {
			glfwPollEvents();
		}
		bool GLWindow::IsWindowOpen() const noexcept {
			return !glfwWindowShouldClose(this->mWindow);
		}
		bool GLWindow::operator~() const noexcept {
			return !glfwWindowShouldClose(this->mWindow);
		}
		void GLWindow::Reset() noexcept {
			if (this->mWindow != nullptr) {
				this->Process();
				glfwDestroyWindow(this->mWindow);
				this->mWindow = nullptr;
			};
			ShadersDestroy();
		}
		uint64_t GLWindow::FrameNo() const noexcept {
			return this->mFrameNo;
		}
		void GLWindow::FrameNoReset() noexcept {
			this->mFrameNo = 0;
		}
		GLWindow::~GLWindow() noexcept {
			this->Reset();
		}

		// PRIVATE

		void GLWindow::SizeCallback(GLFWwindow* apWindow, const int aWidth, const int aHeight) noexcept {
			((GLWindow*)glfwGetWindowUserPointer(apWindow))->HandleUserResize(aWidth, aHeight);
		}
		void GLWindow::HandleUserResize(const uint64_t aWidth, const uint64_t aHeight) noexcept {
			//TODO: add resizing support
#ifdef OPENARABTOOLS_PRINT_DEBUG_INFO
			Error::warning("User window resize.");
#endif
			this->mWidth = aWidth;
			this->mHeight = aHeight;
		}

		void GLWindow::CreateWindow() noexcept {
			if (Error::noiniterror()) return;

			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
			this->mWindow = glfwCreateWindow(this->mWidth, this->mHeight, "OpenArabTools", NULL, NULL);
			glfwSetWindowUserPointer(this->mWindow, this);
			glfwSetWindowSizeCallback(this->mWindow, SizeCallback);
			glfwMakeContextCurrent(this->mWindow);

			glewInit();
			glfwSwapInterval(0);

			glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

			this->glVAO.Bind();
			ShadersInit();
		}

		void GLWindow::ShadersInit() noexcept {
			this->glCircleShader = Internal::MakeShader(Internal::VertexCircleSource, Internal::FragmentCircleSource);
			glUseProgram(this->glCircleShader);
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