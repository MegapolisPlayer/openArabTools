#include "../GLBaseImplementation.hpp"

//disable annoying "possible loss of data" warning
#pragma warning( disable : 4244 ) 

namespace OpenArabTools {
	namespace Internal {
		template<typename DataType, uint64_t Multiplier>
		GLShaderBuffer<DataType, Multiplier>::GLShaderBuffer() noexcept
			: mBuffer(csGLInvalidHandle), mSize(0), mId(csGLInvalidHandle), mInit(false) {}
		template<typename DataType, uint64_t Multiplier>
		GLShaderBuffer<DataType, Multiplier>::GLShaderBuffer(DataType* aData, const uint64_t aAmount, GLVertexArray* const aArray) noexcept {
			aArray->Counter++;
			this->Set<DataType>(aData, aAmount, aArray);
		}

		template<typename DataType, uint64_t Multiplier>
		GLShaderBuffer<DataType, Multiplier>::GLShaderBuffer(GLShaderBuffer&& aOther) noexcept {
			this->mBuffer = aOther.mBuffer;
			aOther.mBuffer = csGLInvalidHandle;
			this->mSize = aOther.mSize;
			aOther.mSize = 0;
			this->mId = aOther.mId;
			aOther.mId = csGLInvalidHandle;
			this->mInit = aOther.mInit;
			aOther.mInit = false;
		}
		template<typename DataType, uint64_t Multiplier>
		GLShaderBuffer<DataType, Multiplier>& GLShaderBuffer<DataType, Multiplier>::operator=(GLShaderBuffer<DataType, Multiplier>&& aOther) noexcept {
			this->mBuffer = aOther.mBuffer;
			aOther.mBuffer = csGLInvalidHandle;
			this->mSize = aOther.mSize;
			aOther.mSize = 0;
			this->mId = aOther.mId;
			aOther.mId = csGLInvalidHandle;
			this->mInit = aOther.mInit;
			aOther.mInit = false;

			return *this;
		}

		template<typename DataType, uint64_t Multiplier>
		void GLShaderBuffer<DataType, Multiplier>::Set(DataType* aData, const uint64_t aAmount, const uint64_t aId, GLVertexArray* const aArray) noexcept {
			if (this->mInit) {
				glDeleteBuffers(1, &this->mBuffer);
				//this could be done better but this isnt much of a performance loss
				//cannot call reset (deletes important variables)
			}
			this->mSize = aAmount;
			this->mId = aId;
			aArray->Bind();
			glGenBuffers(1, &this->mBuffer);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->mBuffer);
			glBufferData(GL_SHADER_STORAGE_BUFFER, this->mSize * sizeof(DataType) * Multiplier, aData, GL_DYNAMIC_DRAW);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, this->mId, this->mBuffer);
			this->mInit = true;
		}

		template<typename DataType, uint64_t Multiplier>
		void GLShaderBuffer<DataType, Multiplier>::Update(DataType* aNewData) noexcept {
			if (!this->mInit) {	Error::error("SSBO not initialized."); return; }

			glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->mBuffer);
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, this->mSize * sizeof(DataType) * Multiplier, aNewData);
		}

		template<typename DataType, uint64_t Multiplier>
		void GLShaderBuffer<DataType, Multiplier>::Bind() noexcept {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->mBuffer);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, this->mId, this->mBuffer);
		}
		template<typename DataType, uint64_t Multiplier>
		void GLShaderBuffer<DataType, Multiplier>::BindBuffer() noexcept {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->mBuffer);
		}
		template<typename DataType, uint64_t Multiplier>
		void GLShaderBuffer<DataType, Multiplier>::Unbind() noexcept {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, this->mId, 0);
		}
		template<typename DataType, uint64_t Multiplier>
		void GLShaderBuffer<DataType, Multiplier>::Reset() noexcept {
			if (!this->mInit) return;
			glDeleteBuffers(1, &this->mBuffer);
			this->mBuffer = csGLInvalidHandle;
			this->mSize = 0;
			this->mId = 0;
			this->mInit = false;
		}

		template<typename DataType, uint64_t Multiplier>
		GLHandle GLShaderBuffer<DataType, Multiplier>::GetHandle() const noexcept {
			return this->mBuffer;
		}
		template<typename DataType, uint64_t Multiplier>
		uint64_t GLShaderBuffer<DataType, Multiplier>::GetSize() const noexcept {
			return this->mSize;
		}

		template<typename DataType, uint64_t Multiplier>
		GLShaderBuffer<DataType, Multiplier>::~GLShaderBuffer() noexcept {
			this->Reset();
		}
	}
}

//reset back
#pragma warning( default : 4244 ) 