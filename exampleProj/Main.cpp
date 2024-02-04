#include <iostream>
#include "OpenArabTools.hpp"
#include <random>
#include <iomanip>

int main() {
	ArabTools::init();
	
	/*
	ArabTools::Matrix m = ArabTools::Matrix(3, 3);
	m.setColor(0, ArabTools::LightColor(ArabTools::LIGHTCOLOR_RED));
	m.showWindow();
	m.run();
	*/

	ArabTools::Semaphore s;
	s.setGreenOn();
	s.setYellowOn();
	s.setRedOn();
	s.showWindow();
	s.run();
		
	ArabTools::terminate();

	char a; std::cin >> a;
}