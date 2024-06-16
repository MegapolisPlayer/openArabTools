#include "OpenArabTools.hpp"

namespace OpenArabTools {
	//declared in Utils.hpp

	bool Internal::IsInit = false;

	bool isLibInit() noexcept {
		return Internal::IsInit;
	}

	void init() noexcept {
		if (Internal::IsInit) return; //no double init
		//GLFW validation
		if (glfwInit() == GLFW_FALSE) {
			Error::error("GLFW window library initialization failed.");
			return;
		}
		//GLFW setup
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		//GLEW validation - create fake 1x1 window
		GLFWwindow* FakeWindow = glfwCreateWindow(1, 1, "temp", NULL, NULL);
		glfwMakeContextCurrent(FakeWindow);
		GLenum GLFWInitializationError = glewInit();
		if (!GLFWInitializationError) {
			std::cerr << glewGetErrorString(GLFWInitializationError) << " (" << GLFWInitializationError << ")\n";
			Error::error("GLEW OpenGL loading library initialization failed.");
			return;
		}
		glfwDestroyWindow(FakeWindow);
		Internal::IsInit = true;
	}

	void terminate() noexcept {
		if (!Internal::IsInit) return;
		glfwTerminate();
		Internal::IsInit = false;
	}

	//increment build for each update, major or minor

	constexpr const char* version() noexcept {
		return
			"OpenArabTools version 0.1.0 build 1, (C) Copyright 2023-2024 Martin/MegapolisPlayer and contributors.\n"
			"Licensed under the Creative Commons CC-BY 4.0 license.\n"
			"Based on ArabTools 1.5.37 (19.03.2020), (C) Copyright 2014-2020 Ing. Daniel Kahoun. All rights reserved.\n";
	}

	constexpr uint64_t buildID() noexcept {
		return 1;
		//0.1.0 release        -> build 1
	}
}
