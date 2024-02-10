#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();
	
	ArabTools::Matrix m;

	m.set(5, 5);
	m.resizeMatrix(3, 3);
	
	for (int i = 0; i < 9; i++) {
		m.setBackground(i, ArabTools::LIGHTCOLOR_YELLOW);
		m.setColor(i, ArabTools::LIGHTCOLOR_BLUE);
		m.setOffColor(i, ArabTools::LIGHTCOLOR_CYAN);
		m.setOnOff(i, i % 2);
		m.mColor[i].Print();
	}
	m.showWindow();
	m.run();
	
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