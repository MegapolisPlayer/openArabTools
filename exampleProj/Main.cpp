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

#define MT_AMOUNT 100000

int main() {
	ArabTools::init();

	ArabTools::Utils::sleep(1000);

	std::cout << ArabTools::Version() << "\n";

	ArabTools::Utils::runConcurrently(MT_AMOUNT, false, Function);

	std::cout << "\nAmount executed 1: " << Test.load() << "\n";

	ArabTools::Internal::GLWindow window;

	float* verticesdata;
	uint64_t vertsize = ArabTools::Internal::GenerateTileVertices(&verticesdata, 5, 5);
	unsigned int* indicesdata;
	ArabTools::Internal::GenerateTileIndices(&indicesdata, vertsize / 4);

	ArabTools::Internal::Debug::PrintVertexArray(&verticesdata, vertsize, 4);
	ArabTools::Internal::Debug::PrintIndexArray(&indicesdata, vertsize / 4, 6);

	ArabTools::Internal::ApplyChangesV(&verticesdata, vertsize, &window.glVBO);
	window.glVBO.EnableAttribute(2, &window.glVAO);
	window.glVBO.EnableAttribute(2, &window.glVAO);
	ArabTools::Internal::ApplyChangesI(&indicesdata, vertsize / 4, &window.glIBO);

	window.PrepareUniforms(5, 5);

	ArabTools::Internal::CircleColor cca[25];

	for (int i = 0; i < 25; i++) {
		//FG-ON, FG-OFF, BG
		cca[i] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0 };
	}

	ArabTools::Internal::GLShaderBuffer<ArabTools::Internal::CircleColor> ssbo;
	ssbo.Set(cca, 25, &window.glVAO);
	ssbo.Bind();

	unsigned int IsOn[] = {
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0
	};

	ArabTools::Internal::GLShaderBuffer<unsigned int> ssbo2;
	ssbo2.Set(IsOn, 25, &window.glVAO);
	ssbo2.Bind();

	while (~window) {
		window.SetBackground(1.0f, 0.0f, 1.0f, 1.0f); //purple bg if something wrong
		window.glIBO.Draw();
		window.Process();
	}

	window.Destroy();
	
	std::cout << "\nAmount executed 2: " << Test.load() << "\n";

	while (Test.load() != MT_AMOUNT);

	std::cout << "Terminating..." << "\n";

	ArabTools::terminate();

	char a; std::cin >> a;
}