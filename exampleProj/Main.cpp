//Demo program
#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();
	
	ArabTools::Matrix m = ArabTools::Matrix(2, 2);
	//m = ArabTools::Matrix(7, 2);
	
	{
		ArabTools::Matrix m2 = m;
		m2.setBackground(ArabTools::LIGHTCOLOREX_DARK_GREEN);
		m2.showWindowAndRun();
	}

	m.setBackground(ArabTools::LIGHTCOLOR_BLUE);
	m.showWindowAndRun();

	ArabTools::terminate();
}