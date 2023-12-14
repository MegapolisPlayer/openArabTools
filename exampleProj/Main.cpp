#include <iostream>
#include "OpenArabTools.hpp"
#include <random>

/*
std::random_device sRandomDevice;
std::mt19937_64 sRandomGenerator(sRandomDevice());
std::uniform_real_distribution<double> DecDistrib(0, 1);
*/

std::atomic<uint16_t> Test = 0;

void Function(const ArabTools::U08 a, const ArabTools::U64 b) {
	Test++;
	return;
}

int main() {
	std::cout << ArabTools::Utils::Version() << "\n";

	ArabTools::Utils::RunConcurrently(1000, false, Function);

	std::cin.get();
	std::cout << Test << "\n";

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