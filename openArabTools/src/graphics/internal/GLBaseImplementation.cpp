#include "GLBaseImplementation.hpp"

//disable annoying "possible loss of data" warning
#pragma warning( disable : 4244 ) 

namespace OpenArabTools {
	namespace Internal {
		//VAO object

		GLVertexArray::GLVertexArray() noexcept {
			glGenVertexArrays(1, &this->Array);
			glBindVertexArray(this->Array);
			this->Counter = 0;
		}

		void GLVertexArray::Bind() noexcept {
			glBindVertexArray(this->Array);
		}
		void GLVertexArray::Unbind() noexcept {
			glBindVertexArray(0);
		}

		GLVertexArray::~GLVertexArray() noexcept {
			glDeleteVertexArrays(1, &this->Array);
		}

		//VBO object

		GLVertexBuffer::GLVertexBuffer() noexcept {
			this->mBuffer = GLInvalidHandle;
			this->mVertices = 0;
			this->mVertSize = 0;
			this->mVertCounter = 0;
			this->mInit = false;
		}
		GLVertexBuffer::GLVertexBuffer(float* const aData, const U64 aVertices, const U64 aVerticesSize) noexcept {
			this->Set(aData, aVertices, aVerticesSize);
		}

		void GLVertexBuffer::Set(float* const aData, const U64 aVertices, const U64 aVerticesSize) noexcept {
			this->mVertices = aVertices;
			this->mVertSize = aVerticesSize;
			glGenBuffers(1, &this->mBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, this->mBuffer);
			glBufferData(GL_ARRAY_BUFFER, this->mVertices * this->mVertSize * sizeof(float), aData, GL_STATIC_DRAW);
			this->mInit = true;
		}

		void GLVertexBuffer::EnableAttribute(const U64 aAmountValues, GLVertexArray* const aArray) noexcept {
			aArray->Bind();
			glEnableVertexAttribArray(aArray->Counter);
			glVertexAttribPointer(aArray->Counter, aAmountValues, GL_FLOAT, GL_FALSE, this->mVertSize * sizeof(float), (const void*)(this->mVertCounter * sizeof(float)));
			aArray->Counter++;
			this->mVertCounter += aAmountValues;
		}
		void GLVertexBuffer::EnableAttribute(const U64 aCounterOverride, const U64 aAmountValues, GLVertexArray* const aArray) noexcept {
			aArray->Bind();
			glEnableVertexAttribArray(aCounterOverride);
			glVertexAttribPointer(aCounterOverride, aAmountValues, GL_FLOAT, GL_FALSE, this->mVertSize * sizeof(float), (const void*)(this->mVertCounter * sizeof(float)));
		}

		void GLVertexBuffer::Bind() noexcept {
			glBindBuffer(GL_ARRAY_BUFFER, this->mBuffer);
		}
		void GLVertexBuffer::Unbind() noexcept {
			glBindBuffer(GL_ARRAY_BUFFER, this->mBuffer);
		}
		void GLVertexBuffer::Reset() noexcept {
			if (!this->mInit) return;
			glDeleteBuffers(1, &this->mBuffer);
			this->mBuffer = GLInvalidHandle;
			this->mVertices = 0;
			this->mVertSize = 0;
			this->mVertCounter = 0;
			this->mInit = false;
		}

		GLHandle GLVertexBuffer::GetHandle() const noexcept {
			return this->mBuffer;
		}
		U64 GLVertexBuffer::GetNumberOfVertices() const noexcept {
			return this->mVertices;
		}
		U64 GLVertexBuffer::GetSizeOfVertex() const noexcept {
			return this->mVertSize;
		}
		U64 GLVertexBuffer::GetAmountOfNumbers() const noexcept {
			return this->mVertices * this->mVertSize;
		}

		GLVertexBuffer::~GLVertexBuffer() noexcept {
			this->Reset();
		}

		//Vertices Generation


		//Generates vertices as:
		//POSX, POSY, TLX, TLY
		// Position , Top Left

		U64 GenerateTileVertices(float** const aBuffer, const U64 aCircleAmountX, const U64 aCircleAmountY) noexcept {
			U64 VerticesAmount = aCircleAmountX * aCircleAmountY * 4;

			*aBuffer = (float*)malloc(sizeof(float) * VerticesAmount * 4);
			if (*aBuffer == nullptr) {
				std::cout << "openArabTools: Vertex Generation error: allocation failed" << "\n";
				return INT_MAX;
			}

			//use 0,0 to 2,2 - we offset everything by -1
			//i - beginning vertex
			//j - local vertex
			//k - local incrementer

			float CircleSizeX = (2.0 / aCircleAmountX);
			float CircleSizeY = (2.0 / aCircleAmountY);

			//for each object
			for (U64 i = 0; i < VerticesAmount; i += 4) {
				//for each vertex in object
				for (U64 j = 0; j < 4; j++) {
					//size * cleaned id + if right/bottom - offset
					//X generation: X size * column + if right
					(*aBuffer)[(i + j) * 4] = (CircleSizeX * int((i / 4) % aCircleAmountX)) + ((j == 1 || j == 2) ? CircleSizeX : 0) - 1.0;
					//Y generation: Y size * row + if bottom * -1 because OpenGL Y coords is flipped
					(*aBuffer)[(i + j) * 4 + 1] = -((CircleSizeY * int((i / 4) / aCircleAmountY)) + ((j == 2 || j == 3) ? CircleSizeY : 0) - 1.0);

					//top left coords
					(*aBuffer)[(i + j) * 4 + 2] = (*aBuffer)[i * 4 + 0];
					(*aBuffer)[(i + j) * 4 + 3] = (*aBuffer)[i * 4 + 1];
				}
			}

			return VerticesAmount;
		}
		void ApplyChangesV(float** const aBuffer, const U64 aAmount, GLVertexBuffer* const aObject) noexcept {
			aObject->Set(*aBuffer, aAmount, 4);
			free(*aBuffer);
		}

		//IBO object

		GLIndexBuffer::GLIndexBuffer() noexcept {
			this->mBuffer = GLInvalidHandle;
			this->mAmount = 0;
			this->mInit = false;
		}
		GLIndexBuffer::GLIndexBuffer(unsigned int* const aData, const U64 aAmount) noexcept {
			this->Set(aData, aAmount);
		}

		void GLIndexBuffer::Set(unsigned int* const aData, const U64 aAmount) noexcept {
			this->mAmount = aAmount;
			glGenBuffers(1, &this->mBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mAmount * sizeof(unsigned int), aData, GL_STATIC_DRAW);
		}

		void GLIndexBuffer::Bind() noexcept {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mBuffer);
		}
		void GLIndexBuffer::Unbind() noexcept {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		void GLIndexBuffer::Reset() noexcept {
			if (!this->mInit) return;
			glDeleteBuffers(1, &this->mBuffer);
			this->mBuffer = GLInvalidHandle;
			this->mAmount = 0;
			this->mInit = false;
		}

		void GLIndexBuffer::Draw(const U64 aOffsetNumbers, const U64 aAmountToDraw) noexcept {
			glDrawElements(GL_TRIANGLES, aAmountToDraw == 0 ? this->mAmount : aAmountToDraw, GL_UNSIGNED_INT, (const void*)(aOffsetNumbers * sizeof(unsigned int)));
		}

		GLHandle GLIndexBuffer::GetHandle() const noexcept {
			return this->mBuffer;
		}
		U64 GLIndexBuffer::GetNumberOfIndices() const noexcept {
			return this->mAmount;
		}

		GLIndexBuffer::~GLIndexBuffer() noexcept {
			this->Reset();
		}

		//Indices generation

		void GenerateTileIndices(unsigned int** aBuffer, const U64 aAmount) {
			*aBuffer = (unsigned int*)malloc(sizeof(unsigned int) * aAmount * 6);
			if (*aBuffer == nullptr) {
				std::cout << "openArabTools: Index Generation error: allocation failed" << "\n";
				return;
			}

			// 6 indices per object (4 vertices)
			// pattern:
			// 0,1,2,2,3,0

			for (U64 i = 0; i < aAmount; i++) {
				(*aBuffer)[i * 6] = i * 4;
				(*aBuffer)[i * 6 + 1] = i * 4 + 1;
				(*aBuffer)[i * 6 + 2] = i * 4 + 2;
				(*aBuffer)[i * 6 + 3] = (*aBuffer)[i * 6 + 2];
				(*aBuffer)[i * 6 + 4] = i * 4 + 3;
				(*aBuffer)[i * 6 + 5] = (*aBuffer)[i * 6];
			}

		}
		void ApplyChangesI(unsigned int** const aBuffer, const U64 aAmount, GLIndexBuffer* const aObject) noexcept {
			aObject->Set(*aBuffer, aAmount * 6);
			free(*aBuffer);
		}

		[[nodiscard]] GLHandle MakeShader(const char* aVertSource, const char* aFragSource) noexcept {
			GLHandle Shader = glCreateProgram();
			GLHandle VertexShader = glCreateShader(GL_VERTEX_SHADER);
			GLHandle FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(VertexShader, 1, &aVertSource, NULL);
			glCompileShader(VertexShader);
			glShaderSource(FragmentShader, 1, &aFragSource, NULL);
			glCompileShader(FragmentShader);

			S32 CompiledVS;
			glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &CompiledVS);
			if (CompiledVS == GL_FALSE) {
				char Buffer[100]; int size;
				glGetShaderInfoLog(VertexShader, 100, &size, Buffer);
				std::cout << "openArabTools: Vertex Shader error: " << Buffer << "\n";
				return GLInvalidHandle;
			}
			S32 CompiledFS;
			glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &CompiledFS);
			if (CompiledFS == GL_FALSE) {
				char Buffer[100]; int size;
				glGetShaderInfoLog(FragmentShader, 100, &size, Buffer);
				std::cout << "openArabTools: Fragment Shader error: " << Buffer << "\n";
				return GLInvalidHandle;
			}

			if (CompiledVS == GL_FALSE || CompiledFS == GL_FALSE) { return GLInvalidHandle; }

			glAttachShader(Shader, VertexShader);
			glAttachShader(Shader, FragmentShader);
			glLinkProgram(Shader);
			glValidateProgram(Shader);
			glDetachShader(Shader, VertexShader);
			glDetachShader(Shader, FragmentShader);
			glDeleteShader(VertexShader);
			glDeleteShader(FragmentShader);

			return Shader;
		}

		//Circles
		//2 POS, 4 COLOR+ALPHA, 4 BG, 2 TOPLEFT
		const char* const VertexCircleSource =
			"#version 460 core\n"
			"in int gl_VertexID;\n"
			"layout(location = 0) in vec2 Position;\n"
			"layout(location = 1) in vec2 TopLeft;\n"
			"out vec2 FragTopLeft;\n"
			"flat out int ObjectID;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(Position.x, Position.y, 1.0, 1.0);\n"
			"	FragTopLeft = TopLeft;\n"
			"	ObjectID = int(gl_VertexID / 4);\n"
			"}\n"
			;
		const char* const FragmentCircleSource =
			"#version 460 core\n"
			"struct ColorInfo {\n"
			"float FR;\n"
			"float FG;\n"
			"float FB;\n"
			"float FA;\n"
			"float OR;\n"
			"float OG;\n"
			"float OB;\n"
			"float OA;\n"
			"float BR;\n"
			"float BG;\n"
			"float BB;\n"
			"float BA;\n"
			"};\n"
			"in vec4 gl_FragCoord;\n"
			"in vec2 FragTopLeft;\n"
			"flat in int ObjectID;\n"
			"out vec4      OutColor;\n"
			"uniform vec2  Size;\n"
			"uniform vec2  WindowResolution;\n"
			"uniform float IRadius;\n" //internal radius
			"uniform float ERadius;\n" //external radius
			"layout(std430, binding = 2) buffer ColorBuffer\n"
			"{\n"
			"	ColorInfo ColorInformation[];\n"
			"};\n"
			"layout(std430, binding = 3) buffer OnBuffer\n"
			"{\n"
			"	bool IsLightOn[];\n"
			"};\n"
			"void main()\n"
			"{\n"
			"	vec2 CenterPoint = vec2(FragTopLeft.x+(Size.x/2), FragTopLeft.y-(Size.y/2));\n"
			"	vec2 UV = vec2(((gl_FragCoord.x/WindowResolution.x)-0.5)*2, ((gl_FragCoord.y/WindowResolution.y)-0.5)*2);\n"
			"	float ActualDistance = distance(CenterPoint, UV);\n"
			"	float ResultCircle = step(ERadius - (ERadius - IRadius), ActualDistance) * (1.0 - step(ERadius, ActualDistance));\n"
			"OutColor = vec4("
			"	vec4(ResultCircle) * vec4(ColorInformation[ObjectID].FR, ColorInformation[ObjectID].FG, ColorInformation[ObjectID].FB, ColorInformation[ObjectID].FA) * vec4(IsLightOn[ObjectID]) +"
			"	vec4(ResultCircle) * vec4(ColorInformation[ObjectID].OR, ColorInformation[ObjectID].OG, ColorInformation[ObjectID].OB, ColorInformation[ObjectID].OA) * vec4(!IsLightOn[ObjectID])"
			") + vec4("
			"	vec4(1.0 - ResultCircle) * vec4(ColorInformation[ObjectID].BR, ColorInformation[ObjectID].BG, ColorInformation[ObjectID].BB, ColorInformation[ObjectID].BA)"
			");\n"
			"}\n"
			;

		/*
		whole calculation of color

		OutColor = vec4(
			vec4(ResultCircle) * vec4(ColorInformation[ObjectID].FR, ColorInformation[ObjectID].FG, ColorInformation[ObjectID].FB, ColorInformation[ObjectID].FA) * vec4(IsLightOn[ObjectID]) +
			vec4(ResultCircle) * vec4(ColorInformation[ObjectID].OR, ColorInformation[ObjectID].OG, ColorInformation[ObjectID].OB, ColorInformation[ObjectID].OA) * vec4(!IsLightOn[ObjectID])
		) + vec4(
			vec4(1.0 - ResultCircle) * vec4(ColorInformation[ObjectID].BR, ColorInformation[ObjectID].BG, ColorInformation[ObjectID].BB, ColorInformation[ObjectID].BA)
		);

		*/

		namespace Debug {
			void PrintVertexArray(float** aArray, const U64 aAmountOfVertices, const U64 aVertexSize, const U64 aVertexPrecisionOverride) noexcept {
				std::ios DefaultCout(nullptr); std::cout.copyfmt(DefaultCout);
				std::cout << std::fixed << std::setprecision(aVertexPrecisionOverride);
				for (uint64_t i = 0; i < aAmountOfVertices * aVertexSize; i++) {
					if (i % aVertexSize == 0 && i != 0) std::cout << '\n';
					std::cout << (*aArray)[i] << ',';
				}
				std::cout << '\n';
				std::cout.copyfmt(DefaultCout);
			}
			void PrintIndexArray(unsigned int** aArray, const U64 aAmountOfObjects, const U64 aIndicesPerObject, const U64 aNumberWidthOverride) noexcept {
				for (uint64_t i = 0; i < aAmountOfObjects * aIndicesPerObject; i++) {
					if (i % aIndicesPerObject == 0 && i != 0) std::cout << '\n';
					std::cout << std::setw(aNumberWidthOverride) << std::setfill('0') << (*aArray)[i] << ',';
				}
				std::cout << '\n';
			}
		}
	}
}