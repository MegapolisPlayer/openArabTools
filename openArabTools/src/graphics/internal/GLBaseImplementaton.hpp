#pragma once
#include "../../types/LightColor.hpp"

namespace OpenArabTools {
	namespace Internal {
		//OpenGL Handle type
		typedef uint32_t GLHandle;
		//OpenGL Invalid handle
		constexpr static GLHandle GLInvalidHandle = INT32_MAX;

		//OpenGL Vertex Array Object
		class OPENARABTOOLS_OBJ GLVertexArray {
		public:
			//Constructor
			GLVertexArray() noexcept;

			//Create a VAO
			void Create() noexcept;
			//Bind
			void Bind() noexcept;
			//Unbind
			void Unbind() noexcept;
			//Reset
			void Reset() noexcept;

			//Gets the handle
			GLHandle GetHandle() const noexcept;

			//Destructor
			~GLVertexArray() noexcept;
		private:
			GLHandle mArray;
			bool mInit;
		};

		//OpenGL Vertex Buffer Object
		class OPENARABTOOLS_OBJ GLVertexBuffer {
		public:
			//Constructor
			GLVertexBuffer() noexcept;

			//Set new data for vertex buffer
			void Set() noexcept;

			//Bind
			void Bind() noexcept;
			//Unbind
			void Unbind() noexcept;
			//Reset
			void Reset() noexcept;

			//Gets the handle
			GLHandle GetHandle() const noexcept;
			//Gets amount of numbers per vertex
			U64 GetNumberAmount() const noexcept;
			//Gets number of vertices in buffer
			U64 GetVertexAmount() const noexcept;

			//Destructor
			~GLVertexBuffer() noexcept;
		private:
			GLHandle mBuffer;
			U64 mNoPerVertex;
			U64 mVertices;
		};

		//OpenGL Index Buffer Object
		class OPENARABTOOLS_OBJ GLIndexBuffer {
		public:
			GLIndexBuffer() noexcept;

			~GLIndexBuffer() noexcept;
		private:
			GLHandle mBuffer;
		};

		//OpenGL Shader Object
		class OPENARABTOOLS_OBJ GLShader {
		public:
			GLShader() noexcept;

			~GLShader() noexcept;
		private:
			GLHandle mShader;
		};

		//OpenGL Transform Object
		class OPENARABTOOLS_OBJ GLTransform {
		public:
			GLTransform() noexcept;

			~GLTransform() noexcept;
		private:

		};

		//OpenGL Camera Object
		class OPENARABTOOLS_OBJ GLCamera {
		public:
			GLCamera() noexcept;

			~GLCamera() noexcept;
		private:

		};
	}
}