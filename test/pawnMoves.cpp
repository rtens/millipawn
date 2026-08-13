#include "../lib/include/Game.h"
#include "base.h"

void pawnMoves() {
	test("start moves", []() {
		Game g;
		g.start("/p/////P");

		should(pm(g.moves(48)), ",a2a3,a2a4");
		should(pm(g.moves(8)), ",a7a6,a7a5");
	});

	test("normal move", []() {
		Game g;
		g.start("//p///P//");

		should(pm(g.moves(40)), ",a3a4");
		should(pm(g.moves(16)), ",a6a5");
	});

	test("blocked", []() {
		Game g;
		g.start("////PP/P/PP");

		should(pm(g.moves(48)), "");
		should(pm(g.moves(40)), "");
		should(pm(g.moves(49)), ",b2b3");
	});

	test("capture", []() {
		Game g;
		g.start("/2ppp/3P//3p/2PPP");

		should(pm(g.moves(19)), ",d6c7,d6e7");
		should(pm(g.moves(35)), ",d4c3,d4e3");
	});

	test("capture on left edge", []() {
		Game g;
		g.start("7p/pp/P//p6P/PP");
		should(pm(g.moves(16)), ",a6b7");
		should(pm(g.moves(32)), ",a4b3");
	});

	test("capture on right edge", []() {
		Game g;
		g.start("/6pp/p6P//7p/6PP/P");
		should(pm(g.moves(23)), ",h6g7");
		should(pm(g.moves(39)), ",h4g3");
	});

	test("white promotes with move", []() {
		Game g;
		g.start("8/1P");
		should(pm(g.moves(9)), ",b7b8q,b7b8r,b7b8n,b7b8b");

		auto moves = g.moves(9);

		g.make(moves[0]);
		should(g.fen().substr(0, 6), "1Q6/8/");
		g.start("8/1P");
		g.make(moves[1]);
		should(g.fen().substr(0, 6), "1R6/8/");
		g.start("8/1P");
		g.make(moves[2]);
		should(g.fen().substr(0, 6), "1N6/8/");
		g.start("8/1P");
		g.make(moves[3]);
		should(g.fen().substr(0, 6), "1B6/8/");
	});

	test("black promotes with move", []() {
		Game g;
		g.start("8//////1p/");
		should(pm(g.moves(49)), ",b2b1q,b2b1r,b2b1n,b2b1b");

		auto moves = g.moves(49);

		g.make(moves[0]);
		should(g.fen().substr(11, 6), "/8/1q6");
		g.start("//////1p/8");
		g.make(moves[1]);
		should(g.fen().substr(11, 6), "/8/1r6");
		g.start("//////1p/8");
		g.make(moves[2]);
		should(g.fen().substr(11, 6), "/8/1n6");
		g.start("//////1p/8");
		g.make(moves[3]);
		should(g.fen().substr(11, 6), "/8/1b6");
	});

	test("white promotes with capture", []() {
		Game g;
		g.start("ppp/1P");
		should(pm(g.moves(9)), ",b7a8q,b7a8r,b7a8n,b7a8b,b7c8q,b7c8r,b7c8n,b7c8b");
	});

	test("black promotes with capture", []() {
		Game g;
		g.start("//////1p/PPP");
		should(pm(g.moves(49)), ",b2a1q,b2a1r,b2a1n,b2a1b,b2c1q,b2c1r,b2c1n,b2c1b");
	});
}
