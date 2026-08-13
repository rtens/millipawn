#include "../lib/include/Game.h"
#include "base.h"

void rookMoves() {
	test("free", []() {
		Game g;
		g.start("///3R");
		should(pm(g.moves(27)),
					 ",d5d6,d5d7,d5d8"
					 ",d5c5,d5b5,d5a5"
					 ",d5e5,d5f5,d5g5,d5h5"
					 ",d5d4,d5d3,d5d2,d5d1");
	});

	test("blocked", []() {
		Game g;
		g.start("/3P//1P1R2P/3P");
		should(pm(g.moves(27)),
					 ",d5d6"
					 ",d5c5"
					 ",d5e5,d5f5");
	});

	test("capture", []() {
		Game g;
		g.start("/3p//1p1R2p/3p");
		should(pm(g.moves(27)),
					 ",d5d6,d5d7"
					 ",d5c5,d5b5"
					 ",d5e5,d5f5,d5g5"
					 ",d5d4");
	});
}
