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

		//VBO generation utils

		//Generates vertices as:
		//POSX, POSY, COLORR, COLORG, COLORB, COLORA, BGR, BGG, BGB, BGA, TLX, TLY
		// Position ,       Foreground (circle)     ,     Background    , Top Left
		 
		OPENARABTOOLS_OBJ void SetColorOfVertex(float** const aBuffer, const U64 aId, const Dec aR, const Dec aG, const Dec aB, const U64 aA = 1.0) noexcept;
		OPENARABTOOLS_OBJ void SetBackgroundOfVertex(float** const aBuffer, const U64 aId, const Dec aR, const Dec aG, const Dec aB, const U64 aA = 1.0) noexcept;
		OPENARABTOOLS_OBJ void SetColorOfCircle(float** const aBuffer, const U64 aId, const Dec aR, const Dec aG, const Dec aB, const U64 aA = 1.0) noexcept;
		OPENARABTOOLS_OBJ void SetBackgroundOfCircle(float** const aBuffer, const U64 aId, const Dec aR, const Dec aG, const Dec aB, const U64 aA = 1.0) noexcept;

		//TODO: SetGradientOfCircle, SetGradientBackgroundOfCircle

		//Allocates memory, returns amount of vertices.
		OPENARABTOOLS_OBJ U64 GenerateTileVertices(float** const aBuffer, const U64 aCircleAmountX, const U64 aCircleAmountY) noexcept;
		//Frees memory allocated by GenerateTileVertices
		OPENARABTOOLS_OBJ void ApplyChangesV(float** const aBuffer, const U64 aAmount, GLVertexBuffer* const aObject) noexcept;

		class OPENARABTOOLS_OBJ GLIndexBuffer {
		public:
			GLIndexBuffer() noexcept;
			GLIndexBuffer(unsigned int* const aData, const U64 aAmount) noexcept;

			void Set(unsigned int* const aData, const U64 aAmount) noexcept;

			void Bind() noexcept;
			void Unbind() noexcept;
			void Reset() noexcept;

			void Draw(const U64 aOffsetNumbers = 0, const U64 aAmountToDraw = 0) noexcept;

			GLHandle GetHandle() const noexcept;
			U64 GetNumberOfIndices() const noexcept;

			~GLIndexBuffer() noexcept;
		private:
			GLHandle mBuffer;
			U64 mAmount;
			bool mInit;
		};

		//IBO generation

		//Allocates memory, takes amount of OBJECTS (**NOT** vertices!!)
		OPENARABTOOLS_OBJ void GenerateTileIndices(unsigned int** aBuffer, const U64 aAmount);
		//Frees memory allocated by GenerateTileIndices, also takes amount of OBJECTS (**NOT** vertices!!)
		OPENARABTOOLS_OBJ void ApplyChangesI(unsigned int** const aBuffer, const U64 aAmount, GLIndexBuffer* const aObject) noexcept;

		OPENARABTOOLS_OBJ [[nodiscard]] GLHandle MakeShader(const char* aVertSource, const char* aFragSource) noexcept;

		//Shader variables, instantiated by Init() in OpenArabTools.cpp

		OPENARABTOOLS_OBJ extern const char* const VertexBackgroundSource;
		OPENARABTOOLS_OBJ extern const char* const VertexCircleSource;

		OPENARABTOOLS_OBJ extern const char* const FragmentBackgroundSource;
		OPENARABTOOLS_OBJ extern const char* const FragmentCircleSource;

		//Shaders defined in GLWindow.hpp and GLWindow.cpp (must be in OpenGL context!)

		OPENARABTOOLS_OBJ GLHandle GetUniform(const GLHandle aShader, const char* aName) noexcept;

		//Debug functions, not user-facing
		namespace Debug {
			OPENARABTOOLS_OBJ void PrintVertexArray(float** aArray, const U64 aAmountOfVertices, const U64 aVertexSize, const U64 aVertexPrecisionOverride = 2) noexcept;
			OPENARABTOOLS_OBJ void PrintIndexArray(unsigned int** aArray, const U64 aAmountOfObjects, const U64 aIndicesPerObject, const U64 aNumberWidthOverride = 4) noexcept;
		}
	}
}