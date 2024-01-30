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

	//TODO: finish rule of 5 functions, copy doesnt work in Matrix!!!!!!!!!!!

	//while (true) {
		ArabTools::Matrix m = ArabTools::Matrix(5, 5);
		ArabTools::Matrix m2(m);
		m2.setColor(ArabTools::LightColor(ArabTools::LIGHTCOLOR_RED));
		m2.setOff(0);
		m2.setOff(5);
		m2.setOff(10);
		m2.setOff(15);
		m2.setOff(20);
		m2.showWindow();
		m2.run();
			
	//}
	

	/*
	ArabTools::Internal::GLWindow win;
	{
		ArabTools::Internal::GLWindow win2(win);
		win2.ShowWindow();

		while (win2.IsWindowOpen()) {
			win2.SetBackground(1.0f);
			win2.Process();
		}
	}

	win.ShowWindow();
	win.BindContext();
	while (win.IsWindowOpen()) {
		win.SetBackground(1.0f, 0.5f, 0.5f, 1.0f);
		win.Process();
	}
	*/

	ArabTools::terminate();
}