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

	{
	ArabTools::Internal::GLWindow window;

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

	ArabTools::Internal::ApplyChangesV(&verticesdata, vertsize, &window.glVBO);
	window.glVBO.EnableAttribute(2, &window.glVAO);
	window.glVBO.EnableAttribute(4, &window.glVAO);
	window.glVBO.EnableAttribute(4, &window.glVAO);
	window.glVBO.EnableAttribute(2, &window.glVAO);
	ArabTools::Internal::ApplyChangesI(&indicesdata, vertsize / 4, &window.glIBO);

	window.PrepareUniforms(5, 5);

	unsigned int IsOn[] = {
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0
	};

	ArabTools::Internal::GLShaderBuffer<unsigned int> ssbo;
	ssbo.Set(IsOn, 25, &window.glVAO);
	ssbo.Bind();

	while (~window) {
		window.SetBackground(0.5f, 1.0f, 0.5f, 1.0f);
		window.glIBO.Draw();
		window.Process();
	}
	}

	std::cout << "\nAmount executed 2: " << Test.load() << "\n";

	ArabTools::terminate();

	char a; std::cin >> a;
}