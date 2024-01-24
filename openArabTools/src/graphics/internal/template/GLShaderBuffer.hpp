#include "../GLBaseImplementation.hpp"

//disable annoying "possible loss of data" warning
#pragma warning( disable : 4244 ) 

namespace OpenArabTools {
	namespace Internal {
		template<typename DataType>
		GLShaderBuffer<DataType>::GLShaderBuffer() noexcept {
			this->mBuffer = GLInvalidHandle;
			this->mSize = 0;
			this->mVAOCount = GLInvalidHandle;
			this->mInit = false;
		}
		template<typename DataType>
		GLShaderBuffer<DataType>::GLShaderBuffer(DataType* aData, const U64 aAmount, GLVertexArray* const aArray) noexcept {
			aArray->Counter++;
			this->Set<DataType>(aData, aAmount, aArray);
		}

		template<typename DataType>
		void GLShaderBuffer<DataType>::Set(DataType* aData, const U64 aAmount, GLVertexArray* const aArray) noexcept {
			if (this->mVAOCount == GLInvalidHandle) { this->mVAOCount = aArray->Counter; }
			this->mSize = aAmount;
			aArray->Bind();
			glGenBuffers(1, &this->mBuffer);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->mBuffer);
			glBufferData(GL_SHADER_STORAGE_BUFFER, this->mSize * sizeof(DataType), aData, GL_DYNAMIC_DRAW);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, this->mVAOCount, this->mBuffer);
			this->mInit = true;
		}

		template<typename DataType>
		void GLShaderBuffer<DataType>::Bind() noexcept {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->mBuffer);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, this->mVAOCount, this->mBuffer);
		}
		template<typename DataType>
		void GLShaderBuffer<DataType>::BindBuffer() noexcept {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->mBuffer);
		}
		template<typename DataType>
		void GLShaderBuffer<DataType>::Unbind() noexcept {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, this->mVAOCount, 0);
		}
		template<typename DataType>
		void GLShaderBuffer<DataType>::Reset() noexcept {
			if (!this->mInit) return;
			glDeleteBuffers(1, &this->mBuffer);
			this->mBuffer = GLInvalidHandle;
			this->mSize = 0;
			this->mVAOCount = GLInvalidHandle;
			this->mInit = false;
		}

		template<typename DataType>
		GLHandle GLShaderBuffer<DataType>::GetHandle() const noexcept {
			return this->mBuffer;
		}
		template<typename DataType>
		U64 GLShaderBuffer<DataType>::GetSize() const noexcept {
			return this->mSize;
		}

		template<typename DataType>
		GLShaderBuffer<DataType>::~GLShaderBuffer() noexcept {
			this->Reset();
		}
	}
}

//reset back
#pragma warning( enable : 4244 ) 