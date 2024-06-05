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
			this->mBuffer = csGLInvalidHandle;
			this->mVertices = 0;
			this->mVertSize = 0;
			this->mInit = false;
		}
		GLVertexBuffer::GLVertexBuffer(float* const arData, const uint64_t aVertices, const uint64_t aVerticesSize) noexcept {
			this->Set(arData, aVertices, aVerticesSize);
		}

		void GLVertexBuffer::Set(float* const arData, const uint64_t aVertices, const uint64_t aVerticesSize) noexcept {
			if (this->mInit) { this->Reset(); }
			this->mVertices = aVertices;
			this->mVertSize = aVerticesSize;
			glGenBuffers(1, &this->mBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, this->mBuffer);
			glBufferData(GL_ARRAY_BUFFER, this->mVertices * this->mVertSize * sizeof(float), arData, GL_STATIC_DRAW);
			this->mInit = true;
		}

		void GLVertexBuffer::EnableAttribute(const uint64_t aAmountValues, GLVertexArray* const apArray) noexcept {
			if (!this->mInit) return;
			apArray->Bind();
			this->Bind();
			glEnableVertexAttribArray(apArray->Counter);
			glVertexAttribPointer(apArray->Counter, aAmountValues, GL_FLOAT, GL_FALSE, this->mVertSize * sizeof(float), (const void*)(std::accumulate(this->mCounterOffsets.begin(), this->mCounterOffsets.end(), 0) * sizeof(float)));
			this->mCounters.push_back(apArray->Counter);
			this->mCounterOffsets.push_back(aAmountValues);
			apArray->Counter++;
		}
		void GLVertexBuffer::EnableAttribute(const uint64_t aCounterOverride, const uint64_t aAmountValues, GLVertexArray* const apArray) noexcept {
			if (!this->mInit) return;
			apArray->Bind();
			this->Bind();
			glEnableVertexAttribArray(aCounterOverride);
			glVertexAttribPointer(aCounterOverride, aAmountValues, GL_FLOAT, GL_FALSE, this->mVertSize * sizeof(float), (const void*)(std::accumulate(this->mCounterOffsets.begin(), this->mCounterOffsets.end(), 0) * sizeof(float)));
			this->mCounters.push_back(aCounterOverride);
			this->mCounterOffsets.push_back(aAmountValues);
		}

		void GLVertexBuffer::RestoreAttributes(GLVertexArray* const apArray) noexcept {
			apArray->Bind();
			this->Bind();
			for (uint64_t i = 0; i < this->mCounters.size(); i++) {
				glEnableVertexAttribArray(this->mCounters[i]);
				glVertexAttribPointer(
					this->mCounters[i], this->mCounterOffsets[i], GL_FLOAT, GL_FALSE, this->mVertSize * sizeof(float),
					(const void*)(std::accumulate(this->mCounterOffsets.begin(), this->mCounterOffsets.begin() + i, 0) * sizeof(float))
				);
			}
		}

		void GLVertexBuffer::Bind() noexcept {
			glBindBuffer(GL_ARRAY_BUFFER, this->mBuffer);
		}
		void GLVertexBuffer::Unbind() noexcept {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		void GLVertexBuffer::Reset() noexcept {
			if (!this->mInit) { return; }
			this->Unbind();
			glDeleteBuffers(1, &this->mBuffer);
			this->mBuffer = csGLInvalidHandle;
			this->mVertices = 0;
			this->mVertSize = 0;
			this->mInit = false;
		}
		void GLVertexBuffer::ResetVectors() noexcept {
			this->mCounters.clear();
			this->mCounterOffsets.clear();
		}

		bool GLVertexBuffer::AreCountersSaved() const noexcept {
			return !(this->mCounters.empty() && this->mCounterOffsets.empty());
		}

		GLHandle GLVertexBuffer::GetHandle() const noexcept {
			return this->mBuffer;
		}
		uint64_t GLVertexBuffer::GetNumberOfVertices() const noexcept {
			return this->mVertices;
		}
		uint64_t GLVertexBuffer::GetSizeOfVertex() const noexcept {
			return this->mVertSize;
		}
		uint64_t GLVertexBuffer::GetAmountOfNumbers() const noexcept {
			return this->mVertices * this->mVertSize;
		}

		GLVertexBuffer::~GLVertexBuffer() noexcept {
			this->Reset();
		}

		//Vertices Generation


		//Generates vertices as:
		//POSX, POSY, TLX, TLY
		// Position , Top Left

		static constexpr uint64_t csVertexSize = 4;

		uint64_t GenerateTileVertices(float** const aprBuffer, const uint64_t aCircleAmountX, const uint64_t aCircleAmountY) noexcept {
			uint64_t VerticesAmount = aCircleAmountX * aCircleAmountY * 4;

			*aprBuffer = (float*)malloc(sizeof(float) * VerticesAmount * csVertexSize);
			if (*aprBuffer == nullptr) {
				Error::error("Vertex Generation error: allocation failed");
				return INT_MAX;
			}

			//use 0,0 to 2,2 - we offset everything by -1
			//i - beginning vertex
			//j - local vertex
			//k - local incrementer

			float CircleSizeX = (2.0 / aCircleAmountX);
			float CircleSizeY = (2.0 / aCircleAmountY);

			//for each object
			for (uint64_t i = 0; i < VerticesAmount; i += 4) {
				//for each vertex in object
				for (uint64_t j = 0; j < 4; j++) {
					//size * id of column + if on right - offset
					(*aprBuffer)[(i + j) * csVertexSize + 0] = (CircleSizeX * (int(i / csVertexSize) % aCircleAmountX) + ((j == 1 || j == 2) ? CircleSizeX : 0)) - 1.0;
					//size * id of row + if on bottom - offset
					(*aprBuffer)[(i + j) * csVertexSize + 1] = -((CircleSizeY * int(i / csVertexSize / aCircleAmountX) + ((j == 2 || j == 3) ? CircleSizeY : 0)) - 1.0);
					
					//top left coords
					(*aprBuffer)[(i + j) * csVertexSize + 2] = (*aprBuffer)[i * csVertexSize + 0];
					(*aprBuffer)[(i + j) * csVertexSize + 3] = (*aprBuffer)[i * csVertexSize + 1];
				}
			}

			return VerticesAmount;
		}
		void ApplyChangesV(float** const appBuffer, const uint64_t aAmount, GLVertexBuffer* const aObject) noexcept {
			aObject->Set(*appBuffer, aAmount, 4);
			free(*appBuffer);
		}

		//IBO object

		GLIndexBuffer::GLIndexBuffer() noexcept {
			this->mBuffer = csGLInvalidHandle;
			this->mAmount = 0;
			this->mInit = false;
		}
		GLIndexBuffer::GLIndexBuffer(unsigned int* const arData, const uint64_t aAmount) noexcept {
			this->Set(arData, aAmount);
		}

		void GLIndexBuffer::Set(unsigned int* const arData, const uint64_t aAmount) noexcept {
			if (this->mInit) { this->Reset(); }
			this->mAmount = aAmount;
			glGenBuffers(1, &this->mBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mAmount * sizeof(unsigned int), arData, GL_STATIC_DRAW);
			this->mInit = true;
		}

		void GLIndexBuffer::Bind() noexcept {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mBuffer);
		}
		void GLIndexBuffer::Unbind() noexcept {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		void GLIndexBuffer::Reset() noexcept {
			if (!this->mInit) { return; }
			this->Unbind();
			glDeleteBuffers(1, &this->mBuffer);
			this->mBuffer = csGLInvalidHandle;
			this->mAmount = 0;
			this->mInit = false;
		}

		void GLIndexBuffer::Draw(const uint64_t aOffsetNumbers, const uint64_t aAmountToDraw) noexcept {
			this->Bind();
			glDrawElements(GL_TRIANGLES, aAmountToDraw == 0 ? this->mAmount : aAmountToDraw, GL_UNSIGNED_INT, (const void*)(aOffsetNumbers * sizeof(unsigned int)));
		}

		GLHandle GLIndexBuffer::GetHandle() const noexcept {
			return this->mBuffer;
		}
		uint64_t GLIndexBuffer::GetNumberOfIndices() const noexcept {
			return this->mAmount;
		}

		GLIndexBuffer::~GLIndexBuffer() noexcept {
			this->Reset();
		}

		//Indices generation

		void GenerateTileIndices(unsigned int** aBuffer, const uint64_t aAmount) {
			*aBuffer = (unsigned int*)malloc(sizeof(unsigned int) * aAmount * 6);
			if (*aBuffer == nullptr) {
				Error::error("Index Generation error: allocation failed"); return;
			}

			// 6 indices per object (4 vertices)
			// pattern:
			// 0,1,2,2,3,0

			for (uint64_t i = 0; i < aAmount; i++) {
				(*aBuffer)[i * 6] = i * 4;
				(*aBuffer)[i * 6 + 1] = i * 4 + 1;
				(*aBuffer)[i * 6 + 2] = i * 4 + 2;
				(*aBuffer)[i * 6 + 3] = (*aBuffer)[i * 6 + 2];
				(*aBuffer)[i * 6 + 4] = i * 4 + 3;
				(*aBuffer)[i * 6 + 5] = (*aBuffer)[i * 6];
			}

		}
		void ApplyChangesI(unsigned int** const aBuffer, const uint64_t aAmount, GLIndexBuffer* const aObject) noexcept {
			aObject->Set(*aBuffer, aAmount * 6);
			free(*aBuffer);
		}

		[[nodiscard]] GLHandle MakeShader(const char* arVertSource, const char* arFragSource) noexcept {
			GLHandle Shader = glCreateProgram();
			GLHandle VertexShader = glCreateShader(GL_VERTEX_SHADER);
			GLHandle FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(VertexShader, 1, &arVertSource, NULL);
			glCompileShader(VertexShader);
			glShaderSource(FragmentShader, 1, &arFragSource, NULL);
			glCompileShader(FragmentShader);

			int32_t CompiledVS;
			glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &CompiledVS);
			if (CompiledVS == GL_FALSE) {
				char Buffer[100]; int size;
				glGetShaderInfoLog(VertexShader, 100, &size, Buffer);
				Error::error("Vertex Shader error: ", Buffer);
				return csGLInvalidHandle;
			}
			int32_t CompiledFS;
			glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &CompiledFS);
			if (CompiledFS == GL_FALSE) {
				char Buffer[100]; int size;
				glGetShaderInfoLog(FragmentShader, 100, &size, Buffer);
				Error::error("Fragment Shader error: ", Buffer);
				return csGLInvalidHandle;
			}

			if (CompiledVS == GL_FALSE || CompiledFS == GL_FALSE) { return csGLInvalidHandle; }

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
			"layout(location = 0) in vec2 Position;\n"
			"layout(location = 1) in vec2 TopLeft;\n"
			"in int VertexID;\n"
			"out vec2 FragTopLeft;\n"
			"flat out int ObjectID;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(Position.x, Position.y, 1.0, 1.0);\n"
			"	ObjectID = int(gl_VertexID / 4);\n"
			"	FragTopLeft = TopLeft;\n"
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
			"	vec2 UV = gl_FragCoord.xy / WindowResolution.xy; //UV coords\n"
			"	UV = UV * 2.0 - 1.0;\n"
			"	vec2 CenterPoint = vec2(FragTopLeft.x+(Size.x/2), FragTopLeft.y-(Size.y/2));\n"
			"	float Aspect = WindowResolution.x / WindowResolution.y;\n"
			"	UV.x *= Aspect;\n"
			"	CenterPoint.x *= Aspect;\n"
			"	float ERadiusM = ERadius * Aspect;\n" //we set stuff in Window::PrepareUniform
			"	float ActualDistance = distance(CenterPoint, UV);\n"
									//if >IRadius and not(>ERadiusM) then we are good
			"	float ResultCircle = step(IRadius, ActualDistance) * (1.0 - step(ERadiusM, ActualDistance));\n"
				//F - foreground, O - off color, B - background
			"	vec4 CF = vec4(ColorInformation[ObjectID].FR, ColorInformation[ObjectID].FG, ColorInformation[ObjectID].FB, ColorInformation[ObjectID].FA);\n"
			"	vec4 CO = vec4(ColorInformation[ObjectID].OR, ColorInformation[ObjectID].OG, ColorInformation[ObjectID].OB, ColorInformation[ObjectID].OA);\n"
			"	vec4 CB = vec4(ColorInformation[ObjectID].BR, ColorInformation[ObjectID].BG, ColorInformation[ObjectID].BB, ColorInformation[ObjectID].BA);\n"
			"	OutColor = ("
					//either CF or CO
			"		(CF * vec4(ResultCircle) * vec4(CF.w) * vec4(IsLightOn[ObjectID])) + "
			"		(CO * vec4(ResultCircle) * vec4(CO.w) * vec4(!IsLightOn[ObjectID])) + "
					//background on outside always, if OFF.alpha != 1 or FG.alpha != 1: background everywhere
			"		(CB * vec4(1.0 - ResultCircle)) + "
			"		(CB * vec4(ResultCircle) * vec4(1.0 - CO.w) * vec4(!IsLightOn[ObjectID])) + "
			"		(CB * vec4(ResultCircle) * vec4(1.0 - CF.w) * vec4(IsLightOn[ObjectID]))"
			"	);\n"
			"}\n"
			;

		namespace Debug {
			void PrintVertexArray(float** aprArray, const uint64_t aAmountOfVertices, const uint64_t aVertexSize, const uint64_t aVertexPrecisionOverride) noexcept {
				std::ios DefaultCout(nullptr); std::cerr.copyfmt(DefaultCout);
				std::cerr << std::fixed << std::setprecision(aVertexPrecisionOverride);
				for (uint64_t i = 0; i < aAmountOfVertices * aVertexSize; i++) {
					if (i % aVertexSize == 0 && i != 0) std::cerr << '\n';
					std::cerr << (*aprArray)[i] << ',';
				}
				std::cerr << '\n';
				std::cerr.copyfmt(DefaultCout);
			}
			void PrintIndexArray(unsigned int** aprArray, const uint64_t aAmountOfObjects, const uint64_t aIndicesPerObject, const uint64_t aNumberWidthOverride) noexcept {
				for (uint64_t i = 0; i < aAmountOfObjects * aIndicesPerObject; i++) {
					if (i % aIndicesPerObject == 0 && i != 0) std::cerr << '\n';
					std::cerr << std::setw(aNumberWidthOverride) << std::setfill('0') << (*aprArray)[i] << ',';
				}
				std::cerr << '\n';
			}
		}
	}
}