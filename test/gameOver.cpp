#include "../lib/include/Game.h"
#include "base.h"

void gameOver() {
	test("not over", []() {
		Game g;
		g.start("/4k3/4Q3/4R3 b");
		should(g.isOver(), 0);
	});

	test("checkmate", []() {
		Game g;
		g.start("4k3/4Q3/4R3 b");
		should(g.isOver(), Game::CHECKMATE);
	});

	test("stalemate", []() {
		Game g;
		g.start("7k/5Q b");
		should(g.isOver(), Game::STALEMATE);
	});

	test("checkmate in one", [](){
		Game g;
		g.start(
					 "r1b2knr/ppq2ppp/3p1b2/1B1P4/5P2/2P5/P5PP/RNBQR1K1 w - -");
		g.make(Move{60, 4});
		should(g.isOver(), Game::CHECKMATE);
	});
}
