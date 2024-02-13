#include "OpenArabTools.hpp"

int main() {
	ArabTools::init();
	

	ArabTools::Chessboard c;

	c.put(4, 4, ArabTools::CHESSBOARD_PIECE_WHITE);	
	c.put(2, 4, ArabTools::CHESSBOARD_PIECE_BLACK);

	for (int i = 0; i < c.getSize(); i++) {
		std::cout << int(c.get(i)) << ' ';
	}
	std::cout << std::endl;

	c.showWindowAndRun();
	
	ArabTools::terminate();
}