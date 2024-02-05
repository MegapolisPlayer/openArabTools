#include <iostream>
#include "OpenArabTools.hpp"
#include <random>
#include <iomanip>

int main() {
	ArabTools::init();
	
	/*
	ArabTools::Matrix m = ArabTools::Matrix(3, 3);
	m.showWindow();

	int i = 0;
	ArabTools::LightColor LC;
	while (m.update()) {
		LC.Set(ArabTools::LightColorD(rand() % 23));
		m.setColor(i % 9, LC);
		m.setOnOff(i % 9, rand() % 2);
		i++;
	}

	*/

	ArabTools::Semaphore s;
	s.setRedOff();
	s.setYellowOff();
	s.setGreenOff();
	s.showWindow();

	#define INT_TIME 750
	while (s.update()) {
		s.setYellowOff();
		s.setRedOn();
		ArabTools::Utils::sleep(INT_TIME);
		s.setYellowOn();
		ArabTools::Utils::sleep(INT_TIME);
		s.setRedOff();
		s.setYellowOff();
		s.setGreenOn();
		ArabTools::Utils::sleep(INT_TIME);
		s.setGreenOff();
		s.setYellowOn();
		ArabTools::Utils::sleep(INT_TIME);
	}
		
	ArabTools::terminate();
}