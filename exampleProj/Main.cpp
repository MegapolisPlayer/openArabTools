#include <iostream>
#include "OpenArabTools.hpp"
#include <random>

/*
std::random_device sRandomDevice;
std::mt19937_64 sRandomGenerator(sRandomDevice());
std::uniform_real_distribution<double> DecDistrib(0, 1);
*/


std::atomic<uint64_t> Test = 0;

void Function(const ArabTools::U08 a, const ArabTools::U64 b) {
	Test++;
	return;
}


int main() {
	ArabTools::Init();

	//ArabTools::Utils::Sleep(1000);

	std::cout << ArabTools::Utils::Version() << "\n";

	ArabTools::Utils::RunConcurrently(100000, true, Function);

	std::cout << "\nAmount executed 1: " << Test.load() << "\n";

	ArabTools::Internal::GLWindow window;
	
	float Vertices[] = {
		-0.5f,  0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f,
	};
	
	/*
	float Vertices[] = {
		-0.9f,  0.9f,
		 0.9f,  0.9f,
		 0.9f, -0.9f,
		-0.9f, -0.9f,
	};
	*/

	ArabTools::Internal::GLVertexBuffer vbo;
	vbo.Set(Vertices, 4, 2);
	vbo.EnableAttribute(2, &window.glVAO);

	unsigned int Indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	ArabTools::Internal::GLIndexBuffer ibo;
	ibo.Set(Indices, 6);

	glUseProgram(window.glCircleShader);
	glUniform2f(window.glCSUResolution, 500, 500);

	while (~window) {
		window.SetBackground(0.5f, 0.5f, 0.5f, 1.0f);
		ibo.Draw();
		window.Process();
	}
	
	std::cout << "\nAmount executed 2: " << Test.load() << "\n";

	ArabTools::Terminate();
}