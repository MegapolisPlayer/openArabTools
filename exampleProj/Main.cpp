#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();

	/*
	ArabTools::Matrix m;
	m.set(3, 3);
	m.setBackground(0, ArabTools::LIGHTCOLOR_RED);
	m.setBackground(1, ArabTools::LIGHTCOLOR_GREEN);
	m.setBackground(2, ArabTools::LIGHTCOLOR_BLUE);
	m.setOn(0);
	m.setOn(1);
	m.setOn(2);
	m.showWindow();
	m.run();
	*/

	ArabTools::Semaphore s2(ArabTools::SemaphoreOrientation::NORMAL);
	ArabTools::Semaphore s = s2;
	s.showWindow();

	#define INT_TIME 750
	while (s.update()) {
		s.setYellowOff();
		s.setRedOn();
		s.sleep(INT_TIME);
		s.setYellowOn();
		s.sleep(INT_TIME);
		s.setRedOff();
		s.setYellowOff();
		s.setGreenOn();
		s.sleep(INT_TIME);
		s.setGreenOff();
		s.setYellowOn();
		s.sleep(INT_TIME);
	}
		
	ArabTools::terminate();
}