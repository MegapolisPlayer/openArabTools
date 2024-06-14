#include "GLWindow.hpp"

//disable annoying "possible loss of data" warning
#pragma warning( disable : 4244 ) 

namespace OpenArabTools {
	namespace Internal {
		//same as normal ArabTools
		uint64_t GLWindow::msDefaultWindowSize = 650;

		//default background: the purple debug one

		GLWindow::GLWindow() noexcept 
			: mWindow(nullptr), mWidth(msDefaultWindowSize), mHeight(msDefaultWindowSize), mFrameNo(0), mTitle("openArabTools"), mBGR(0.7), mBGG(0.0), mBGB(0.7), mBGA(1.0) {
			this->CreateWindow();
		}

		GLWindow::GLWindow(const uint64_t aWidth, const uint64_t aHeight) noexcept
			: mWindow(nullptr), mWidth(aWidth), mHeight(aHeight), mFrameNo(0), mTitle("openArabTools"), mBGR(0.7), mBGG(0.0), mBGB(0.7), mBGA(1.0) {
			this->CreateWindow();
		}

		GLWindow::GLWindow(const GLWindow& aOther) noexcept
			: mWindow(nullptr), mWidth(msDefaultWindowSize), mHeight(msDefaultWindowSize), mFrameNo(0), mTitle("openArabTools"), mBGR(0.7), mBGG(0.0), mBGB(0.7), mBGA(1.0) {
			if (&aOther == this) {
				Error::error("Self-assignment in GLWindow detected."); return;
			}
			this->Reset();
			if (!aOther.mWindow) { return; }

			this->mWidth = aOther.mWidth;
			this->mHeight = aOther.mHeight;
			this->mFrameNo = aOther.mFrameNo;
			this->mTitle = aOther.mTitle;

			this->CreateWindow();

			BufferCopy(aOther, *this);
		}
		GLWindow::GLWindow(GLWindow&& aOther) noexcept
			: mWindow(nullptr), mWidth(msDefaultWindowSize), mHeight(msDefaultWindowSize), mFrameNo(0), mTitle("openArabTools") {
			if (&aOther == this) {
				Error::error("Self-assignment in GLWindow detected."); return;
			}
			if (!aOther.mWindow) { return; }

			this->mWidth = aOther.mWidth;
			this->mHeight = aOther.mHeight;
			this->mFrameNo = aOther.mFrameNo;
			this->mTitle = std::move(aOther.mTitle);

			this->mWindow = aOther.mWindow;
			this->BindContext();

			this->glVAO = std::move(aOther.glVAO);
			this->glVBO = std::move(aOther.glVBO);
			this->glIBO = std::move(aOther.glIBO);

			aOther.mWindow = nullptr;
		}
		GLWindow& GLWindow::operator=(const GLWindow& aOther) noexcept {
			if (&aOther == this) {
				Error::error("Self-assignment in GLWindow detected."); return *this;
			}
			this->Reset();
			if (!aOther.mWindow) { return *this; }

			this->mWidth = aOther.mWidth;
			this->mHeight = aOther.mHeight;
			this->mFrameNo = aOther.mFrameNo;
			this->mTitle = aOther.mTitle;

			this->CreateWindow();

			BufferCopy(aOther, *this);

			return *this;
		}
		GLWindow& GLWindow::operator=(GLWindow&& aOther) noexcept {
			if (&aOther == this) {
				Error::error("Self-assignment in GLWindow detected."); return *this;
			}

			this->Reset();
			if (!aOther.mWindow) { return *this; }

			this->mWidth = aOther.mWidth;
			this->mHeight = aOther.mHeight;
			this->mFrameNo = aOther.mFrameNo;
			this->mTitle = std::move(aOther.mTitle);

			this->mWindow = aOther.mWindow;
			this->BindContext();

			this->glVAO = std::move(aOther.glVAO);
			this->glVBO = std::move(aOther.glVBO);
			this->glIBO = std::move(aOther.glIBO);

			aOther.mWindow = nullptr;

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
			this->mWidth = aWidth;
			this->mHeight = aHeight;
			glViewport(0, 0, this->mWidth, this->mHeight);
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
			this->mBGR = aAll, this->mBGG = aAll, this->mBGB = aAll, this->mBGA = aAll;
		}
		void GLWindow::SetBackground(const double_t aRGB, const double_t aA) noexcept {
			glClear(GL_COLOR_BUFFER_BIT);
			this->mBGR = aRGB, this->mBGG = aRGB, this->mBGB = aRGB, this->mBGA = aA;
		}
		void GLWindow::SetBackground(const double_t aR, const double_t aG, const double_t aB, const double_t aA) noexcept {
			glClear(GL_COLOR_BUFFER_BIT);
			this->mBGR = aR, this->mBGG = aG, this->mBGB = aB, this->mBGA = aA;
		}
		void GLWindow::BindContext() const noexcept {
			glfwMakeContextCurrent(NULL);
			glfwMakeContextCurrent(this->mWindow);
		}
		void GLWindow::Process() noexcept {
			glfwSwapBuffers(this->mWindow);
			glfwPollEvents();
			this->mFrameNo++;
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(this->mBGR, this->mBGG, this->mBGB, this->mBGA);
		}
		void GLWindow::Events() noexcept {
			glfwPollEvents();
		}
		bool GLWindow::IsWindowOpen() const noexcept {
			return !glfwWindowShouldClose(this->mWindow);
		}
		bool GLWindow::IsWindowHidden() const noexcept {
			return !glfwGetWindowAttrib(this->mWindow, GLFW_VISIBLE);
		}
		bool GLWindow::operator~() const noexcept {
			return !glfwWindowShouldClose(this->mWindow);
		}
		void GLWindow::Reset() noexcept {
			if (this->mWindow != nullptr) {
				glfwMakeContextCurrent(NULL); //important: FREE CONTEXT
				glfwDestroyWindow(this->mWindow);
				this->mWindow = nullptr;
			};
			this->glVBO.Reset();
			this->glIBO.Reset();
		}
		uint64_t GLWindow::FrameNo() const noexcept {
			return this->mFrameNo;
		}
		void GLWindow::FrameNoReset() noexcept {
			this->mFrameNo = 0;
		}
		GLWindow::~GLWindow() noexcept {
			this->glVAO.Reset();
			this->Reset();
		}

		// PRIVATE

		void GLWindow::SizeCallback(GLFWwindow* apWindow, const int aWidth, const int aHeight) noexcept {
			((GLWindow*)glfwGetWindowUserPointer(apWindow))->HandleUserResize(aWidth, aHeight);
		}
		void GLWindow::HandleUserResize(const uint64_t aWidth, const uint64_t aHeight) noexcept {
#ifdef OPENARABTOOLS_PRINT_DEBUG_INFO
			Error::warning("User window resize.");
#endif
			this->mWidth = aWidth;
			this->mHeight = aHeight;
		}

		void GLWindow::CreateWindow() noexcept {
			if (Error::noiniterror()) return;
			if (this->mWindow != nullptr) {
				Error::warning("Double create of GLWindow!");
				this->Reset();
			}

			this->glVAO.Reset(); //new VAO per window

			//glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#ifdef _DEBUG
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); //set debug context for error handling
#endif
			this->mWindow = glfwCreateWindow(this->mWidth, this->mHeight, "OpenArabTools", NULL, NULL);
			glfwSetWindowUserPointer(this->mWindow, this);
			glfwSetWindowSizeCallback(this->mWindow, SizeCallback);
			glfwMakeContextCurrent(this->mWindow);

#ifdef _DEBUG
			glDebugMessageCallback(Internal::GLDebugCallback, nullptr);
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif

			glewInit();
			glfwSwapInterval(0);

			glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

			this->glVAO.Make();
		}

		//OpenGL kinda sucks when copying buffers: save data, switch to different context and upload data back
		//Cannot use glCopy(Named)BufferSubData because objects are in different contexts

		void BufferCopy(const GLWindow& aWindow1, GLWindow& aWindow2) noexcept {
			if (aWindow1.mWindow == nullptr) {
				return;
			}
			if (!aWindow1.glVBO.IsValid() || !aWindow1.glIBO.IsValid()) {
				return; //source buffers invalid, dont copy
			}

			//allocate temp
			GLfloat* VData = (GLfloat*)malloc(aWindow1.glVBO.GetAmountOfNumbers() * sizeof(GLfloat));
			GLuint* IData = (GLuint*)malloc(aWindow1.glIBO.GetNumberOfIndices() * sizeof(GLuint));

			//get data
			aWindow1.BindContext();

			glGetNamedBufferSubData(aWindow1.glVBO.GetHandle(), 0, aWindow1.glVBO.GetAmountOfNumbers() * sizeof(GLfloat), VData);
			glGetNamedBufferSubData(aWindow1.glIBO.GetHandle(), 0, aWindow1.glIBO.GetNumberOfIndices() * sizeof(GLuint), IData);

			//set data
			aWindow2.BindContext();

			aWindow2.glVBO.Set(VData, aWindow1.glVBO.GetNumberOfVertices(), aWindow1.glVBO.GetSizeOfVertex());
			aWindow2.glIBO.Set(IData, aWindow1.glIBO.GetNumberOfIndices());

			//free temp
			free(VData);
			free(IData);
		}

		//Child classes

		//GLWindow cannot init shaders: in CreateWindow(), ShaderInit is called but derived class not yet made! (ShadersInit is different)

		//GLCircleWindow

		GLCircleWindow::GLCircleWindow()
			: GLWindow(), glCircleShader(csGLInvalidHandle), glCSUSize(csGLInvalidHandle), glCSUResolution(csGLInvalidHandle), glCSUInternalRadius(csGLInvalidHandle), glCSUExternalRadius(csGLInvalidHandle) {
			this->ShadersInit();
		}
		GLCircleWindow::GLCircleWindow(const uint64_t aWidth, const uint64_t aHeight) noexcept
			: GLWindow(aWidth, aHeight), glCircleShader(csGLInvalidHandle), glCSUSize(csGLInvalidHandle), glCSUResolution(csGLInvalidHandle), glCSUInternalRadius(csGLInvalidHandle), glCSUExternalRadius(csGLInvalidHandle) {
			this->ShadersInit();
		}
		GLCircleWindow::GLCircleWindow(const GLCircleWindow& aOther) noexcept {
			GLWindow::operator=(aOther);
			this->BindContext();
			this->ShadersDestroy();
			this->ShadersInit();
		}
		GLCircleWindow::GLCircleWindow(GLCircleWindow&& aOther) noexcept
			: GLWindow(std::move(aOther)) {
			this->glCircleShader = aOther.glCircleShader;
			aOther.glCircleShader = csGLInvalidHandle;
			this->glCSUSize = aOther.glCSUSize;
			this->glCSUResolution = aOther.glCSUResolution;
			this->glCSUInternalRadius = aOther.glCSUInternalRadius;
			this->glCSUExternalRadius = aOther.glCSUExternalRadius;
		}
		GLCircleWindow& GLCircleWindow::operator=(const GLCircleWindow& aOther) noexcept {
			GLWindow::operator=(aOther);
			this->BindContext();
			this->ShadersDestroy();
			this->ShadersInit();

			return *this;
		} 
		GLCircleWindow& GLCircleWindow::operator=(GLCircleWindow&& aOther) noexcept {
			GLWindow::operator=(std::move(aOther));
			this->glCircleShader = aOther.glCircleShader;
			aOther.glCircleShader = csGLInvalidHandle;
			this->glCSUSize = aOther.glCSUSize;
			this->glCSUResolution = aOther.glCSUResolution;
			this->glCSUInternalRadius = aOther.glCSUInternalRadius;
			this->glCSUExternalRadius = aOther.glCSUExternalRadius;

			return *this;
		}

		void GLCircleWindow::Resize(const uint64_t aWidth, const uint64_t aHeight) noexcept {
			GLWindow::Resize(aWidth, aHeight); //sets mWidth, mHeight
			glUniform2f(this->glCSUResolution, this->mWidth, this->mHeight);
		}
		void GLCircleWindow::Reset() noexcept {
			GLWindow::Reset();
			this->ShadersDestroy();
		}
		void GLCircleWindow::BindShader() const noexcept {
			glUseProgram(this->glCircleShader);
		}
		void GLCircleWindow::PrepareUniforms(const uint64_t aAmountCirclesX, const uint64_t aAmountCirclesY, const double_t aInternalRadius) noexcept {
			glUseProgram(this->glCircleShader);
			glUniform2f(this->glCSUResolution, this->mWidth, this->mHeight);
			glUniform1f(this->glCSUInternalRadius, aInternalRadius);
			glUniform1f(
				this->glCSUExternalRadius,
				1.0 / aAmountCirclesX
			);
			glUniform2f(this->glCSUSize, 2.0 / aAmountCirclesX, 2.0 / aAmountCirclesY);
		}

		GLCircleWindow::~GLCircleWindow() noexcept {
			this->Reset();
		}

		void GLCircleWindow::ShadersInit() noexcept {
			this->glCircleShader = Internal::MakeShader(Internal::VertexCircleSource, Internal::FragmentCircleSource);
			this->glCSUSize = glGetUniformLocation(this->glCircleShader, "Size");
			this->glCSUResolution = glGetUniformLocation(this->glCircleShader, "WindowResolution");
			this->glCSUInternalRadius = glGetUniformLocation(this->glCircleShader, "IRadius");
			this->glCSUExternalRadius = glGetUniformLocation(this->glCircleShader, "ERadius");
			glUseProgram(this->glCircleShader);
		}
		void GLCircleWindow::ShadersDestroy() noexcept {
			if (this->glCircleShader == csGLInvalidHandle) {
				return;
			}
			glDeleteProgram(this->glCircleShader);
			this->glCircleShader = csGLInvalidHandle;
		}

		//GLPassthroughWindow
		
		GLPassthroughWindow::GLPassthroughWindow() noexcept
			: GLWindow(), glShader(csGLInvalidHandle) {
			this->ShadersInit();
		}
		GLPassthroughWindow::GLPassthroughWindow(const uint64_t aWidth, const uint64_t aHeight) noexcept
			: GLWindow(aWidth, aHeight), glShader(csGLInvalidHandle) {
			this->ShadersInit();
		}
		GLPassthroughWindow::GLPassthroughWindow(const GLCircleWindow& aOther) noexcept 
			: GLWindow(aOther), glShader(csGLInvalidHandle) {
			this->BindContext();
			this->ShadersDestroy();
			this->ShadersInit();
		}
		GLPassthroughWindow::GLPassthroughWindow(GLPassthroughWindow&& aOther) noexcept 
			: GLWindow(aOther), glShader(csGLInvalidHandle) {
			this->glShader = aOther.glShader;
			aOther.glShader = csGLInvalidHandle;
		}
		GLPassthroughWindow& GLPassthroughWindow::operator=(const GLPassthroughWindow& aOther) noexcept {
			GLWindow::operator=(aOther);
			this->BindContext();
			this->ShadersDestroy();
			this->ShadersInit();
			return *this;
		}
		GLPassthroughWindow& GLPassthroughWindow::operator=(GLPassthroughWindow&& aOther) noexcept {
			GLWindow::operator=(std::move(aOther));
			this->glShader = aOther.glShader;
			aOther.glShader = csGLInvalidHandle;
			return *this;
		}

		void GLPassthroughWindow::Reset() noexcept {
			GLWindow::Reset();
			this->ShadersDestroy();
		}
		void GLPassthroughWindow::BindShader() const noexcept {
			glUseProgram(this->glShader);
		}
		GLPassthroughWindow::~GLPassthroughWindow() noexcept {
			this->Reset();
		}

		void GLPassthroughWindow::ShadersInit() noexcept {
			this->glShader = Internal::MakeShader(Internal::VertexPassSource, Internal::FragmentPassSource);
			glUseProgram(this->glShader);
			this->glWindowResolutionUniform = glGetUniformLocation(this->glShader, "WindowResolution");
		}
		void GLPassthroughWindow::ShadersDestroy() noexcept {
			if (this->glShader != csGLInvalidHandle) {
				glDeleteProgram(this->glShader);
				this->glShader = csGLInvalidHandle;
				this->glWindowResolutionUniform = csGLInvalidHandle;
			}
		}
	}
}