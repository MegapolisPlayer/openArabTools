#include "OpenArabTools.hpp"

// Small demo test suite to demonstrate openArabTools

int main() {
	ArabTools::init();

	{
		ArabTools::Dice d(1, 2); //1 tile free space between dots, 2 tiles padding
		d.setBackground(ArabTools::LIGHTCOLOREX_CESKEDRAHY_LIGHT_BLUE);
		d.setColor(ArabTools::LIGHTCOLOREX_CESKEDRAHY_DARK_BLUE);
		uint64_t Counter = 0;
		while (d.update()) {
			d.setValue(Counter % 10); //modulo 10, remainder
			if (!d.sleep(500)) {
				break;
			}; //sleep for 500ms
			Counter++;
		}
	}

	{
		ArabTools::Crossing cross("crossing2.oat");
		cross.showWindowAndRun();
	}

	{
		ArabTools::Matrix m(7, 3); //make a 7x3 matrix

		//enable some lights
		m.setOn(0, 0);
		m.setOn(1, 1);
		m.setOn(2, 0);
		m.setOn(3, 1);
		m.setOn(4, 0);

		//we can set colors AFTER set on/off (but we also can set them before)
		m.setBackground(ArabTools::LIGHTCOLOREX_CESKEDRAHY_DARK_BLUE); //LIGHTCOLOREX enum
		m.setColor(ArabTools::LightColor((uint8_t)255, (uint8_t)255, (uint8_t)0)); //convert to uint8_t to trigger correct constructor
		m.setOffColor(ArabTools::LIGHTCOLOR_DARK_GRAY); //LIGHTCOLOR enum

		m.showWindowAndRun();
	}

	{
		ArabTools::Canvas c;

		ArabTools::Rectangle r;
		r.setColor(ArabTools::LIGHTCOLOR_RED);
		r.setPosition(50, 50);
		r.setWidth(100);
		r.setHeight(200);
		int rh = c.add(r);

		ArabTools::Circle c2;
		c2.setColor(ArabTools::LIGHTCOLOR_BLUE).setPosition(200, 200).setRadius(100);
		int ch = c.add(c2);

		//c.remove(ch);

		c.showWindowAndRun();
	}

	ArabTools::terminate();
}