//Demo program
#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();
	
	//{
	//	ArabTools::Dice d(1, 1);
	//	d.showWindow();
	//	int i = 0;
	//	while (d.update()) {
	//		ArabTools::ScopedTimer st("frame");
	//		d.setValue(i % 10);
	//		d.sleep(500);
	//		i++;
	//	}
	//}
	//
	//{
	//	ArabTools::Chessboard c;
	//	c.put(1, 1, ArabTools::PieceColor::CHESSBOARD_PIECE_BLACK);
	//	c.put(7, 7, ArabTools::PieceColor::CHESSBOARD_PIECE_WHITE);
	//	c.showWindowAndRun();
	//}
	//
	//{
	//	ArabTools::Semaphore s;
	//	s.showWindowAndRun();
	//}

	{
		ArabTools::Crossing cr;

		ArabTools::CrossingSemaphoreAccessor* csa1 = cr.getSemaphore(0);
		ArabTools::CrossingSemaphoreAccessor* csa2 = cr.getSemaphore(1);
		ArabTools::CrossingSemaphoreAccessor* csa3 = cr.getSemaphore(2);
		ArabTools::CrossingSemaphoreAccessor* csa4 = cr.getSemaphore(3);

		csa1->setGreenOn();
		csa2->setGreenOn();
		csa3->setGreenOn();
		csa4->setGreenOn();

		cr.hideSemaphore(0);

		cr.showWindowAndRun();
	}

	ArabTools::terminate();
}