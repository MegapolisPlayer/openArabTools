#include "GLBaseImplementaton.hpp"

namespace OpenArabTools {
	namespace Internal {
		GLVertexArray::GLVertexArray() noexcept {
			glGenVertexArrays(1, &this->mArray);
			this->mInit = true;
		}

		void GLVertexArray::Create() noexcept {
			if (this->mInit) return;
			glGenVertexArrays(1, &this->mArray);
			this->mInit = true;
		}
		void GLVertexArray::Bind() noexcept {
			if (!this->mInit) return;
			glBindVertexArray(this->mArray);
		}
		void GLVertexArray::Unbind() noexcept {
			glBindVertexArray(0);
		}
		void GLVertexArray::Reset() noexcept {
			if (!this->mInit) return;
			glDeleteVertexArrays(1, &this->mArray);
			this->mInit = false;
		}

		GLHandle GLVertexArray::GetHandle() const noexcept {
			if (!this->mInit) return GLInvalidHandle;
			return this->mArray;
		}

		GLVertexArray::~GLVertexArray() noexcept {
			if (!this->mInit) return;
			glDeleteVertexArrays(1, &this->mArray);
		}
	}
}