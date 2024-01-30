#include "OpenArabTools.hpp"

namespace OpenArabTools {
	//declared in Utils.hpp

	U64 Internal::InitAmount = 0;

	bool isLibInit() noexcept {
		return Internal::InitAmount;
	}

	void init() noexcept {
		if (Internal::InitAmount != 0) return; //no double init
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
		if (glewInit()) {
			Error::error("GLEW OpenGL loading library initialization failed.");
			return;
		}
		glfwDestroyWindow(FakeWindow);
		Internal::InitAmount++;
	}

	//TODO: fix terminate()

	void terminate() noexcept {
		//if (Internal::InitAmount == 0) { return; } //if zero: no init
		//if (Internal::InitAmount > 1) { Internal::InitAmount--; return; } //if more than one: just decrement 

		glfwTerminate(); //only when everything freed
		//Internal::InitAmount--;
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