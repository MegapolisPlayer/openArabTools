#pragma once
#include "../../types/LightColor.hpp"

namespace OpenArabTools {
	namespace Internal {
		typedef uint32_t GLHandle;
		constexpr static GLHandle GLInvalidHandle = INT32_MAX;

		class OPENARABTOOLS_OBJ GLVertexBuffer {
		public:
			GLVertexBuffer() noexcept;
			GLVertexBuffer(float* const aData, const U64 aVertices, const U64 aVerticesSize) noexcept;

			void Set(float* const aData, const U64 aVertices, const U64 aVerticesSize) noexcept;

			void EnableAttribute(const U64 aAmountValues, GLHandle* const aArray) noexcept;
			void EnableAttribute(const U64 aCounterOverride, const U64 aAmountValues, GLHandle* const aArray) noexcept;

			void Bind() noexcept;
			void Unbind() noexcept;
			void Reset() noexcept;

			GLHandle GetHandle() const noexcept;
			U64 GetNumberOfVertices() const noexcept;
			U64 GetSizeOfVertex() const noexcept;
			U64 GetAmountOfNumbers() const noexcept;

			~GLVertexBuffer() noexcept;
		private:
			GLHandle mBuffer;
			U64 mVertices;
			U64 mVertSize;
			U64 mCounter;
			U64 mVertCounter;
			bool mInit;
		};

		class OPENARABTOOLS_OBJ GLIndexBuffer {
		public:
			GLIndexBuffer() noexcept;
			GLIndexBuffer(unsigned int* const aData, const U64 aAmount) noexcept;

			void Set(unsigned int* const aData, const U64 aAmount) noexcept;

			void Bind() noexcept;
			void Unbind() noexcept;
			void Reset() noexcept;

			void Draw() noexcept;

			GLHandle GetHandle() const noexcept;
			U64 GetNumberOfIndices() const noexcept;

			~GLIndexBuffer() noexcept;
		private:
			GLHandle mBuffer;
			U64 mAmount;
			bool mInit;
		};

		OPENARABTOOLS_OBJ [[nodiscard]] GLHandle MakeShader(const char* aVertSource, const char* aFragSource) noexcept;

		OPENARABTOOLS_OBJ extern const char* const VertexPassthroughSource;
		OPENARABTOOLS_OBJ extern const char* const VertexCircleSource;

		OPENARABTOOLS_OBJ extern const char* const FragmentPassthroughSource;
		OPENARABTOOLS_OBJ extern const char* const FragmentCircleSource;

		//Shaders defined in GLWindow.hpp and GLWindow.cpp (must be in OpenGL context!)

		OPENARABTOOLS_OBJ GLHandle GetUniform(const GLHandle aShader, const char* aName) noexcept;

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
	}
}