#include "OpenArabTools.hpp"

namespace OpenArabTools {
	//declared in Utils.hpp

	S64 gsInit = false;

	bool isLibInit() noexcept {
		return gsInit;
	}

	void init() noexcept {
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

	void terminate() noexcept {
		if (gsInit != 0) gsInit--; return; //no double terminate

		glfwTerminate(); //only when everything freed
	}

	//increment build for each update, major or minor

	constexpr const char* Version() noexcept {
		return
			"OpenArabTools version 0.1.0 build 0, (C) Copyright 2023-2024 Martin/MegapolisPlayer and contributors.\n"
			"Licensed under the Creative Commons CC-BY 4.0 license.\n"
			"Based on ArabTools 1.5.37 (19.03.2020), (C) Copyright 2014-2020 Ing. Daniel Kahoun. All rights reserved.\n";
	}

	constexpr U64 buildID() noexcept {
		return 0;
		//0.1.0 in development -> builds 0-
		//0.1.0 release        -> build  
	}
}