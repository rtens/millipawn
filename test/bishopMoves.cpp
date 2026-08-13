#include "../lib/include/Game.h"
#include "base.h"

void bishopMoves() {
	test("free", []() {
		Game g;
		g.start("///3B");
		should(pm(g.moves(27)),
					 ",d5c6,d5b7,d5a8"
					 ",d5e6,d5f7,d5g8"
					 ",d5c4,d5b3,d5a2"
					 ",d5e4,d5f3,d5g2,d5h1");
	});

	test("blocked", []() {
		Game g;
		g.start("P//4P/3B//1P3P//");
		should(pm(g.moves(27)), ",d5c6,d5b7,d5c4,d5e4");
	});

	test("capture", []() {
		Game g;
		g.start("p//4p/3B//1p3p//");
		should(pm(g.moves(27)), ",d5c6,d5b7,d5a8,d5e6,d5c4,d5b3,d5e4,d5f3");
	});
}
