#include <iostream>
#include "OpenArabTools.hpp"
#include <random>
#include <iomanip>

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
	ArabTools::init();

	ArabTools::Utils::sleep(1000);

	std::cout << ArabTools::Version() << "\n";

	ArabTools::Utils::runConcurrently(100000, false, Function);

	std::cout << "\nAmount executed 1: " << Test.load() << "\n";

	float* a;
	uint64_t sz = ArabTools::Internal::GenerateTileVertices(&a, 5, 5);
	ArabTools::Internal::GLVertexBuffer vbo2;
	std::cout << std::fixed;
	std::cout << std::setprecision(2);
	for (int i = 0; i < sz * 12; i++) {
		if (i % 12 == 0 && i != 0) {
			std::cout << "\n";
		}
		std::cout << a[i] << ",";
	}
	ArabTools::Internal::ApplyChangesV(&a, &sz, &vbo2);
	std::cout << std::resetiosflags(std::ios_base::basefield);

	ArabTools::Internal::GLWindow window;

	//2 for position, 4 for color+alpha, 2 for top left vertex
	//make AutoGen function in GLBaseImpl
	float Vertices[] = {
		-0.5f,  1.0f, 0.5f, 0.0f, 0.0f, 1.0f, -0.5, 1.0,
		 0.5f,  1.0f, 0.5f, 0.0f, 0.0f, 1.0f, -0.5, 1.0,
		 0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, -0.5, 1.0,
		-0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, -0.5, 1.0,

		-0.5f,  0.5f, 0.5f, 0.5f, 0.0f, 1.0f, -0.5, 0.5,
		 0.5f,  0.5f, 0.5f, 0.5f, 0.0f, 1.0f, -0.5, 0.5,
		 0.5f,  0.0f, 0.5f, 0.5f, 0.0f, 1.0f, -0.5, 0.5, 
		-0.5f,  0.0f, 0.5f, 0.5f, 0.0f, 1.0f, -0.5, 0.5,

		-0.5f,  0.0f, 0.0f, 0.5f, 0.0f, 1.0f, -0.5, 0.0,
		 0.5f,  0.0f, 0.0f, 0.5f, 0.0f, 1.0f, -0.5, 0.0,
		 0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, -0.5, 0.0,
		-0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, -0.5, 0.0,
	};
	
	ArabTools::Internal::GLVertexBuffer vbo;
	vbo.Set(Vertices, 12, 8);
	vbo.EnableAttribute(2, &window.glVAO);
	vbo.EnableAttribute(4, &window.glVAO);
	vbo.EnableAttribute(2, &window.glVAO);

	unsigned int Indices[] = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8
	};

	ArabTools::Internal::GLIndexBuffer ibo;
	ibo.Set(Indices, 18);

	//things that are set for multiple objects: uniform!
	//things unique to every object: attribute!
	//in OpenArabTools - all circles have same size, radius, window resolution (this will be moved to Renderer, Window)
	//TODO: move to renderer, window
	glUseProgram(window.glCircleShader);
	glUniform2f(window.glCSUResolution, 500, 500);
	glUniform1f(window.glCSUInternalRadius, 0.0f);
	glUniform1f(window.glCSUExternalRadius, 0.25f);
	glUniform2f(window.glCSUSize, 1.0, 0.5);

	while (~window) {
		window.SetBackground(0.5f, 0.5f, 0.5f, 1.0f);
		ibo.Draw(); 
		window.Process();
	}

	std::cout << "\nAmount executed 2: " << Test.load() << "\n";
	
	ArabTools::terminate();
}