#pragma once
#include "../../types/LightColor.hpp"

namespace OpenArabTools {
	namespace Internal {
		class OPENARABTOOLS_OBJ GLVertexBuffer {
		public:
			GLVertexBuffer() noexcept;
			
			~GLVertexBuffer() noexcept;
		private:
			unsigned int mBuffer;
		};
		class OPENARABTOOLS_OBJ GLIndexBuffer {
		public:
			GLIndexBuffer() noexcept;

			~GLIndexBuffer() noexcept;
		private:
			unsigned int mBuffer;
		};
		class OPENARABTOOLS_OBJ GLShader {
		public:
			GLShader() noexcept;

			~GLShader() noexcept;
		private:
			unsigned int mShader;
		};
		class OPENARABTOOLS_OBJ GLTransform {
		public:
			GLTransform() noexcept;

			~GLTransform() noexcept;
		private:
			
		};
		class OPENARABTOOLS_OBJ GLCamera {
		public:
			GLCamera() noexcept;

			~GLCamera() noexcept;
		private:
			
		};

		class OPENARABTOOLS_OBJ GLWindow {
		public:
			GLWindow() noexcept;

			void ShowWindow() noexcept;

			void HideWindow() noexcept;

			~GLWindow() noexcept;
		private:
			GLFWwindow* mWindow;
			U64 mWidth, mHeight;
		};
	}
}