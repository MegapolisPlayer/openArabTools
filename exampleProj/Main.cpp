#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();
	
	ArabTools::Matrix m;

	while (true) {
		m.set(5, 5);
		m.resizeMatrix(7, 7);
		m.reset();
	}

	/*
	for (int i = 0; i < 49; i++) {
		m.setBackground(i, ArabTools::LightColorD(i % 16));
		m.setColor(i, ArabTools::LIGHTCOLOR_BLUE);
		m.setOn(i);
		m.mColor[i].Print();
	}
	m.showWindow();
	m.run();
	*/

	//todo: FIX: when resizing matrix cannot set foreground colors (but it is passed to shader successfully and without resize it works!)
	
	/*
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
	*/
		
	ArabTools::terminate();
}