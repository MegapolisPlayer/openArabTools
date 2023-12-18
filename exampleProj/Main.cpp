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
	ArabTools::Manager m;

	std::cout << ArabTools::Utils::Version() << "\n";

	ArabTools::Utils::RunConcurrently(100000, true, Function);

	std::cout << "\nAmount executed 1: " << Test.load() << "\n";

	ArabTools::Internal::GLWindow window;

	while (~window) {
		window.SetBackground(0.5f, 0.5f, 0.5f, 0.5f);
		window.Process();
	}
	
	std::cout << "\nAmount executed 2: " << Test.load() << "\n";
}