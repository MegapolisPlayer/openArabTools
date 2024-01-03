#include "OpenArabTools.hpp"

namespace OpenArabTools {
	//declared in Utils.hpp

	S64 gsInit = false;

	bool IsLibInit() noexcept {
		return gsInit;
	}

	void Init() noexcept {
		if (gsInit != 0) return; //no double init
		//GLFW validation
		if (glfwInit() == GLFW_FALSE) {
			std::cout << "OpenArabTools Error: GLFW window library initialization failed.\n";
			return;
		}
		//GLEW validation - create fake 1x1 window
		GLFWwindow* FakeWindow = glfwCreateWindow(1, 1, "temp", NULL, NULL);
		glfwMakeContextCurrent(FakeWindow);
		if (glewInit()) {
			std::cout << "OpenArabTools Error: GLEW OpenGL loader library initialization failed.\n";
			return;
		}
		glfwDestroyWindow(FakeWindow);
		gsInit++;
	}

	void Terminate() noexcept {
		if (gsInit != 0) gsInit--; return; //no double terminate

		glfwTerminate(); //only when everything freed
	}
}