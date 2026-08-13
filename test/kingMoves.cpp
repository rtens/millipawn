#include "../lib/include/Game.h"
#include "base.h"

void kingMoves() {
	test("free", []() {
		Game g;
		g.start("///3K");
		should(pm(g.moves(27)), ",d5c6,d5d6,d5e6,d5c5,d5e5,d5c4,d5d4,d5e4");
	});

	test("blocked", []() {
		Game g;
		g.start("//2PP/3KP/2PP");
		should(pm(g.moves(27)), ",d5e6,d5c5,d5e4");
	});

	test("capture", []() {
		Game g;
		g.start("//2pP/3Kp/2PP");
		should(pm(g.moves(27)), ",d5c6,d5e6,d5c5,d5e5,d5e4");
	});
}
