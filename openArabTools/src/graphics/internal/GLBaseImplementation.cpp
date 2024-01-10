#include "GLBaseImplementation.hpp"

//disable annoying "possible loss of data" warning
#pragma warning( disable : 4244 ) 

namespace OpenArabTools {
	namespace Internal {
		GLVertexBuffer::GLVertexBuffer() noexcept {
			this->mBuffer = GLInvalidHandle;
			this->mVertices = 0;
			this->mVertSize = 0;
			this->mCounter = 0;
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

		void GLVertexBuffer::EnableAttribute(const U64 aAmountValues, GLHandle* const aArray) noexcept {
			glBindVertexArray(*aArray);
			glEnableVertexAttribArray(this->mCounter);
			glVertexAttribPointer(this->mCounter, aAmountValues, GL_FLOAT, GL_FALSE, this->mVertSize * sizeof(float), (const void*)(this->mVertCounter * sizeof(float)));
			this->mCounter++;
			this->mVertCounter += aAmountValues;
		}
		void GLVertexBuffer::EnableAttribute(const U64 aCounterOverride, const U64 aAmountValues, GLHandle* const aArray) noexcept {
			glBindVertexArray(*aArray);
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
			this->mCounter = 0;
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

		//Circle backgrounds
		//2 POS, 4 COLOR+ALPHA
		const char* const VertexBackgroundSource =
			"#version 330 core\n"
			"layout(location = 0) in vec2 Position;\n"
			"layout(location = 1) in vec4 Color;\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(Position.x, Position.y, 1.0, 1.0);\n"
			"	FragColor = Color;\n"
			"}\n"
			;
		const char* const FragmentBackgroundSource =
			"#version 330 core\n"
			"out vec4 color;\n"
			"in vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"	color = FragColor;\n"
			"}\n"
			;

		//Circles
		//2 POS, 4 COLOR+ALPHA, 2 TOPLEFT
		const char* const VertexCircleSource =
			"#version 330 core\n"
			"layout(location = 0) in vec2 Position;\n"
			"layout(location = 1) in vec4 Color;\n"
			"layout(location = 2) in vec2 TopLeft;\n"
			"out vec4 FragColor;\n"
			"out vec2 FragTopLeft;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(Position.x, Position.y, 1.0, 1.0);\n"
			"	FragColor = Color;\n"
			"	FragTopLeft = TopLeft;\n"
			"}\n"
			;
		const char* const FragmentCircleSource =
			"#version 330 core\n"
			"in vec4 gl_FragCoord;\n"
			"in vec4 FragColor;\n"
			"in vec2 FragTopLeft;\n"
			"out vec4      OutColor;\n"
			"uniform vec2  Size;\n"
			"uniform vec2  WindowResolution;\n"
			"uniform float IRadius;\n"
			"uniform float ERadius;\n"
			"void main()\n"
			"{\n"
			"	vec2 CenterPoint = vec2(FragTopLeft.x+(Size.x/2), FragTopLeft.y-(Size.y/2));\n"
			"	vec2 UV = vec2(((gl_FragCoord.x/WindowResolution.x)-0.5)*2, ((gl_FragCoord.y/WindowResolution.y)-0.5)*2);\n"
			"	float ActualDistance = distance(CenterPoint, UV);\n"
			"	float ResultCircle = step(ERadius - (ERadius - IRadius), ActualDistance) * (1.0 - step(ERadius, ActualDistance));\n"
			"	OutColor = vec4(vec3(ResultCircle) * FragColor.xyz, ResultCircle * FragColor.w);\n"
			"}\n"
			;
	}
}