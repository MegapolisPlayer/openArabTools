#include <iostream>
#include "OpenArabTools.hpp"

int main() {
	std::cout << ArabTools::Utils::Version() << "\n";

	glfwInit();
	GLFWwindow* Window = glfwCreateWindow(500, 500, "ArabTools", NULL, NULL);
	glfwMakeContextCurrent(Window);
	glewInit();

	while (!glfwWindowShouldClose(Window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
	
	glfwTerminate();
}