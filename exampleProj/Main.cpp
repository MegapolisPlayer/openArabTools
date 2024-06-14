#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();

	//ArabTools::Matrix m(7, 3); //make a 7x3 matrix
	//
	////enable some lights
	//m.setOn(0, 0);
	//m.setOn(1, 1);
	//m.setOn(2, 0);
	//m.setOn(3, 1);
	//m.setOn(4, 0);
	//
	////we can set colors AFTER set on/off (but we also can set them before)
	//m.setBackground(ArabTools::LIGHTCOLOREX_CESKEDRAHY_DARK_BLUE); //LIGHTCOLOREX enum
	//m.setColor(ArabTools::LightColor((uint8_t)255, (uint8_t)255, (uint8_t)0)); //convert to uint8_t to trigger correct constructor
	//m.setOffColor(ArabTools::LIGHTCOLOR_DARK_GRAY); //LIGHTCOLOR enum
	//
	//m.showWindowAndRun();

	ArabTools::Canvas c;

	ArabTools::Rectangle r;
	r.setColor(ArabTools::LIGHTCOLOR_RED);
	r.setPosition(0, 0);
	r.setWidth(600);
	r.setHeight(300);
	c.add(r);

	c.showWindowAndRun();

	ArabTools::terminate();
}