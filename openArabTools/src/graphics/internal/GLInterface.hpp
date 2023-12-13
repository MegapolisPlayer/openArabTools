#pragma once
#include "../../StandardInclude.hpp"

namespace OpenArabTools {
	namespace Internal {
		class OPENARABTOOLS_OBJ GLVertexBuffer {
		public:
		private:
			unsigned int mBuffer;
		};
		class OPENARABTOOLS_OBJ GLIndexBuffer {
		public:
		private:
			unsigned int mBuffer;
		};
		class OPENARABTOOLS_OBJ GLShader {
		public:
		private:
			unsigned int mShader;
		};
		class OPENARABTOOLS_OBJ GLTransform {
		public:
		private:
			
		};
		class OPENARABTOOLS_OBJ GLCamera {
		public:
		private:
			
		};

		class OPENARABTOOLS_OBJ GLWindow {
		public:
			GLWindow();

			~GLWindow();
		private:
			GLFWwindow* mWindow;
			U64 mWidth, mHeight;
		};
	}
}