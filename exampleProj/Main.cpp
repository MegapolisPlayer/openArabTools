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

	ArabTools::Internal::GLWindow window;
	ArabTools::Internal::GLVertexBuffer vbo;
	ArabTools::Internal::GLIndexBuffer ibo;

	float* verticesdata;
	uint64_t vertsize = ArabTools::Internal::GenerateTileVertices(&verticesdata, 5, 5);
	unsigned int* indicesdata;
	ArabTools::Internal::GenerateTileIndices(&indicesdata, vertsize / 4);

	for (int i = 0; i < 25; i++) {
		ArabTools::Internal::SetBackgroundOfCircle(&verticesdata, i, NORMAL255(0), NORMAL255(0), NORMAL255(128));
		ArabTools::Internal::SetColorOfCircle(&verticesdata, i, NORMAL255(200), NORMAL255(200), NORMAL255(255));
	}

	ArabTools::Internal::Debug::PrintVertexArray(&verticesdata, vertsize, 12);
	ArabTools::Internal::Debug::PrintIndexArray(&indicesdata, vertsize / 4, 6);

	ArabTools::Internal::ApplyChangesV(&verticesdata, vertsize, &vbo);
	vbo.EnableAttribute(2, &window.glVAO);
	vbo.EnableAttribute(4, &window.glVAO);
	vbo.EnableAttribute(4, &window.glVAO);
	vbo.EnableAttribute(2, &window.glVAO);
	ArabTools::Internal::ApplyChangesI(&indicesdata, vertsize / 4, &ibo);

	//things that are set for multiple objects: uniform!
	//things unique to every object: attribute!
	//in OpenArabTools - all circles have same size, radius, window resolution (this will be moved to Renderer, Window)
	//TODO: move to renderer, window
	//glUseProgram(window.glNormalShader);
	glUseProgram(window.glCircleShader);
	glUniform2f(window.glCSUResolution, 500, 500);
	glUniform1f(window.glCSUInternalRadius, 0.05f);
	glUniform1f(window.glCSUExternalRadius, 0.2f);
	glUniform2f(window.glCSUSize, 0.4f, 0.4f);

	while (~window) {
		std::cout << "Tick " << window.FrameNo() << "\n";
		window.SetBackground(1.0f, 1.0f, 1.0f, 1.0f);
		ibo.Draw();
		window.Process();
	}

	std::cout << "\nAmount executed 2: " << Test.load() << "\n";

	ArabTools::terminate();

	char a; std::cin >> a;
}