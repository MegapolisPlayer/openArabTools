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
		cr.showWindowAndRun();
	}

	ArabTools::terminate();
}