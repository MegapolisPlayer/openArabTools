//
//OpenGL internal interface functions
//

#pragma once
#include "../../types/LightColor.hpp"

namespace OpenArabTools {
	namespace Internal {
		typedef unsigned int GLHandle;

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
			unsigned int mBuffer;
		};

		//OpenGL Shader Object
		class OPENARABTOOLS_OBJ GLShader {
		public:
			GLShader() noexcept;

			~GLShader() noexcept;
		private:
			unsigned int mShader;
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

		//Main Window Class (for OpenGL)
		class OPENARABTOOLS_OBJ GLWindow {
		public:
			//Creates a new OpenGL Window
			GLWindow() noexcept;
			//Creates a new OpenGL Window, with parameters
			GLWindow(const U64 aWidth, const U64 aHeight) noexcept;

			//Shows the window
			void ShowWindow() noexcept;

			//Hides the window
			void HideWindow() noexcept;

			//Sets the title of the window
			void SetTitle(const char* aTitle) noexcept;

			//Resize the window
			void Resize(const U64 aWidth, const U64 aHeight) noexcept;

			//Sets new background
			void SetBackground(const Dec aAll) noexcept;
			//Sets new background
			void SetBackground(const Dec aRGB, const Dec aA) noexcept;
			//Sets new background
			void SetBackground(const Dec aR, const Dec aG, const Dec aB, const Dec aA) noexcept;

			//Processes window events
			void Process() noexcept;

			//Returns if window should be open
			bool IsWindowOpen() noexcept;

			//Operator ~, returns if window should be still open
			bool operator~() noexcept;

			//Gets the window handle
			GLFWwindow* GetWindow() noexcept;

			//Destructor
			~GLWindow() noexcept;
		private:
			GLFWwindow* mWindow;
			U64 mWidth, mHeight;
		};
	}
}