#include <iostream>
#include "OpenArabTools.hpp"
#include <random>
#include <iomanip>

int main() {
	ArabTools::init();
	
	ArabTools::Matrix m = ArabTools::Matrix(5, 5);
	m.setColor(ArabTools::LightColor(ArabTools::LIGHTCOLOR_RED));
	m.setOff(0);
	m.setOff(5);
	m.setOff(10);
	m.setOff(15);
	m.setOff(20);
	m.showWindow();
	m.run();
		
	ArabTools::terminate();

	char a; std::cin >> a;
}