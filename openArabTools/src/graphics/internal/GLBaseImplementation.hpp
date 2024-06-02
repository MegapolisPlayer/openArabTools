#pragma once
#include "../../types/LightColor.hpp"

namespace OpenArabTools {
	namespace Internal {

		typedef uint32_t GLHandle;
		constexpr static GLHandle GLInvalidHandle = INT32_MAX;

		//Fx - foreground on, Ox - foreground off, Bx - background
		struct CircleColor {
			float FR = 0.0, FG = 0.0, FB = 0.0, FA = 0.0;
			float OR = 0.0, OG = 0.0, OB = 0.0, OA = 0.0;
			float BR = 0.0, BG = 0.0, BB = 0.0, BA = 0.0;

			CircleColor() noexcept {}

			CircleColor(float aFR, float aFG, float aFB, float aFA, float aOR, float aOG, float aOB, float aOA, float aBR, float aBG, float aBB, float aBA) noexcept
				: FR(aFR), FG(aFG), FB(aFB), FA(aFA), OR(aOR), OG(aOG), OB(aOB), OA(aOA), BR(aBR), BG(aBG), BB(aBB), BA(aBA) {}

			void SetF(const LightColor& aColor) noexcept {
				FR = aColor.R;
				FG = aColor.G;
				FB = aColor.B;
				FA = 1.0f;
			}
			void SetO(const LightColor& aColor) noexcept {
				OR = aColor.R;
				OG = aColor.G;
				OB = aColor.B;
				OA = 1.0f;
			}
			void SetB(const LightColor& aColor) noexcept {
				BR = aColor.R;
				BG = aColor.G;
				BB = aColor.B;
				BA = 1.0f;
			}

			//debug function
			void Print() noexcept {
				std::cerr << 
					"F " << FR << ' ' << FG << ' ' << FB << ' ' << FA << ' ' <<
					"O " << OR << ' ' << OG << ' ' << OB << ' ' << OA << ' ' <<
					"B " << BR << ' ' << BG << ' ' << BB << ' ' << BA << ' ' <<
					'\n';
			}

			~CircleColor() noexcept {}
		};

		class OPENARABTOOLS_OBJ GLVertexArray {
		public:
			GLVertexArray() noexcept;

			void Bind() noexcept;
			void Unbind() noexcept;

			~GLVertexArray() noexcept;

			GLHandle Array;
			U64 Counter;
		};

		class OPENARABTOOLS_OBJ GLVertexBuffer {
		public:
			GLVertexBuffer() noexcept;
			GLVertexBuffer(float* const aData, const U64 aVertices, const U64 aVerticesSize) noexcept;

			void Set(float* const aData, const U64 aVertices, const U64 aVerticesSize) noexcept;

			void EnableAttribute(const U64 aAmountValues, GLVertexArray* const aArray) noexcept;
			void EnableAttribute(const U64 aCounterOverride, const U64 aAmountValues, GLVertexArray* const aArray) noexcept;

			void RestoreAttributes(GLVertexArray* const aArray) noexcept;

			void Bind() noexcept;
			void Unbind() noexcept;
			void Reset() noexcept;
			void ResetVectors() noexcept;

			bool AreCountersSaved() const noexcept;

			GLHandle GetHandle() const noexcept;
			U64 GetNumberOfVertices() const noexcept;
			U64 GetSizeOfVertex() const noexcept;
			U64 GetAmountOfNumbers() const noexcept;

			~GLVertexBuffer() noexcept;
		private:
			GLHandle mBuffer;
			U64 mVertices;
			U64 mVertSize;
			bool mInit;

			std::vector<U64> mCounters;
			std::vector<U64> mCounterOffsets;
		};

		//VBO generation utils

		//Generates vertices as:
		//POSX, POSY, TLX, TLY
		// Position , Top Left

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

		//Shader variables, instantiated by window classes

		OPENARABTOOLS_OBJ extern const char* const VertexCircleSource;
		OPENARABTOOLS_OBJ extern const char* const FragmentCircleSource;

		//Shaders defined in GLWindow.hpp and GLWindow.cpp (must be in OpenGL context!)

		OPENARABTOOLS_OBJ GLHandle GetUniform(const GLHandle aShader, const char* aName) noexcept;

		//SSBO

		template<typename DataType, U64 Multiplier = 1>
		class GLShaderBuffer {
		public:
			GLShaderBuffer() noexcept;
			GLShaderBuffer(DataType* aData, const U64 aAmount, GLVertexArray* const aArray) noexcept;

			void Set(DataType* aData, const U64 aAmount, GLVertexArray* const aArray) noexcept;
			void Update(DataType* aNewData) noexcept;

			void Bind() noexcept;
			void BindBuffer() noexcept; //bind only the buffer
			void Unbind() noexcept;
			void Reset() noexcept;

			GLHandle GetHandle() const noexcept;
			U64 GetSize() const noexcept;

			~GLShaderBuffer() noexcept;
		private:
			GLHandle mBuffer;
			U64 mSize;
			U64 mVAOCount;
			bool mInit;
		};

		//Debug functions, not user-facing
		namespace Debug {
			OPENARABTOOLS_OBJ void PrintVertexArray(float** aArray, const U64 aAmountOfVertices, const U64 aVertexSize, const U64 aVertexPrecisionOverride = 2) noexcept;
			OPENARABTOOLS_OBJ void PrintIndexArray(unsigned int** aArray, const U64 aAmountOfObjects, const U64 aIndicesPerObject, const U64 aNumberWidthOverride = 4) noexcept;
		}

	} //namespace Internal
} //namespace oAT

#include "template/GLShaderBuffer.hpp"

