#include <iostream>
#include "OpenArabTools.hpp"
#include <random>

std::random_device sRandomDevice;
std::mt19937_64 sRandomGenerator(sRandomDevice());
std::uniform_real_distribution<double> DecDistrib(0, 1);

int main() {
	std::cout << ArabTools::Utils::Version() << "\n" << DecDistrib(sRandomGenerator);

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