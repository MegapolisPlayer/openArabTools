#pragma once
#include "../../types/LightColor.hpp"

namespace OpenArabTools {
	namespace Internal {

		typedef uint32_t GLHandle;
		constexpr static GLHandle csGLInvalidHandle = INT32_MAX;

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
			uint64_t Counter;
		};

		class OPENARABTOOLS_OBJ GLVertexBuffer {
		public:
			GLVertexBuffer() noexcept;
			GLVertexBuffer(float* const aData, const uint64_t aVertices, const uint64_t aVerticesSize) noexcept;

			void Set(float* const aData, const uint64_t aVertices, const uint64_t aVerticesSize) noexcept;

			void EnableAttribute(const uint64_t aAmountValues, GLVertexArray* const aArray) noexcept;
			void EnableAttribute(const uint64_t aCounterOverride, const uint64_t aAmountValues, GLVertexArray* const aArray) noexcept;

			void RestoreAttributes(GLVertexArray* const aArray) noexcept;

			void Bind() noexcept;
			void Unbind() noexcept;
			void Reset() noexcept;
			void ResetVectors() noexcept;

			bool AreCountersSaved() const noexcept;

			GLHandle GetHandle() const noexcept;
			uint64_t GetNumberOfVertices() const noexcept;
			uint64_t GetSizeOfVertex() const noexcept;
			uint64_t GetAmountOfNumbers() const noexcept;

			~GLVertexBuffer() noexcept;
		private:
			GLHandle mBuffer;
			uint64_t mVertices;
			uint64_t mVertSize;
			bool mInit;

			std::vector<uint64_t> mCounters;
			std::vector<uint64_t> mCounterOffsets;
		};

		//VBO generation utils

		//Generates vertices as:
		//POSX, POSY, TLX, TLY
		// Position , Top Left

		//Allocates memory, returns amount of vertices.
		OPENARABTOOLS_OBJ uint64_t GenerateTileVertices(float** const aBuffer, const uint64_t aCircleAmountX, const uint64_t aCircleAmountY) noexcept;
		//Frees memory allocated by GenerateTileVertices
		OPENARABTOOLS_OBJ void ApplyChangesV(float** const aBuffer, const uint64_t aAmount, GLVertexBuffer* const aObject) noexcept;

		class OPENARABTOOLS_OBJ GLIndexBuffer {
		public:
			GLIndexBuffer() noexcept;
			GLIndexBuffer(unsigned int* const aData, const uint64_t aAmount) noexcept;

			void Set(unsigned int* const aData, const uint64_t aAmount) noexcept;

			void Bind() noexcept;
			void Unbind() noexcept;
			void Reset() noexcept;

			void Draw(const uint64_t aOffsetNumbers = 0, const uint64_t aAmountToDraw = 0) noexcept;

			GLHandle GetHandle() const noexcept;
			uint64_t GetNumberOfIndices() const noexcept;

			~GLIndexBuffer() noexcept;
		private:
			GLHandle mBuffer;
			uint64_t mAmount;
			bool mInit;
		};

		//IBO generation

		//Allocates memory, takes amount of OBJECTS (**NOT** vertices!!)
		OPENARABTOOLS_OBJ void GenerateTileIndices(unsigned int** aBuffer, const uint64_t aAmount);
		//Frees memory allocated by GenerateTileIndices, also takes amount of OBJECTS (**NOT** vertices!!)
		OPENARABTOOLS_OBJ void ApplyChangesI(unsigned int** const aBuffer, const uint64_t aAmount, GLIndexBuffer* const aObject) noexcept;

		OPENARABTOOLS_OBJ [[nodiscard]] GLHandle MakeShader(const char* aVertSource, const char* aFragSource) noexcept;

		//Shader variables, instantiated by window classes

		OPENARABTOOLS_OBJ extern const char* const VertexCircleSource;
		OPENARABTOOLS_OBJ extern const char* const FragmentCircleSource;

		//Shaders defined in GLWindow.hpp and GLWindow.cpp (must be in OpenGL context!)

		OPENARABTOOLS_OBJ GLHandle GetUniform(const GLHandle aShader, const char* aName) noexcept;

		//SSBO

		template<typename DataType, uint64_t Multiplier = 1>
		class GLShaderBuffer {
		public:
			GLShaderBuffer() noexcept;
			GLShaderBuffer(DataType* aData, const uint64_t aAmount, GLVertexArray* const aArray) noexcept;

			void Set(DataType* aData, const uint64_t aAmount, GLVertexArray* const aArray) noexcept;
			void Update(DataType* aNewData) noexcept;

			void Bind() noexcept;
			void BindBuffer() noexcept; //bind only the buffer
			void Unbind() noexcept;
			void Reset() noexcept;

			GLHandle GetHandle() const noexcept;
			uint64_t GetSize() const noexcept;

			~GLShaderBuffer() noexcept;
		private:
			GLHandle mBuffer;
			uint64_t mSize;
			uint64_t mVAOCount;
			bool mInit;
		};

		//Debug functions, not user-facing
		namespace Debug {
			OPENARABTOOLS_OBJ void PrintVertexArray(float** aArray, const uint64_t aAmountOfVertices, const uint64_t aVertexSize, const uint64_t aVertexPrecisionOverride = 2) noexcept;
			OPENARABTOOLS_OBJ void PrintIndexArray(unsigned int** aArray, const uint64_t aAmountOfObjects, const uint64_t aIndicesPerObject, const uint64_t aNumberWidthOverride = 4) noexcept;
		}

	} //namespace Internal
} //namespace oAT

#include "template/GLShaderBuffer.hpp"

