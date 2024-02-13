#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();
	
	ArabTools::Dice d(1, 1);
	d.showWindow();
	int i = 0;
	while (true) {
		ArabTools::ScopedTimer st("frame");
		d.update();
		d.setValue(i % 10);
		d.sleep(500);
		i++;
	}

	ArabTools::terminate();
}