#include "../lib/include/Game.h"
#include "base.h"

void enPassant() {
	test("white takes", []() {
		Game g;
		g.start("/3p//2P b");
		g.make(Move{11, 27});
		should(g.fen().substr(g.fen().find_first_of(' '), 8), " w - d6 ");
		should(pm(g.moves(26)), ",c5c6,c5d6");
		g.make(Move{26, 19});
		should(g.fen().substr(0, 24), "8/8/3P4/8/8/8/8/8 b - - ");
	});

	test("black takes", []() {
		Game g;
		g.start("////4p//3P w");
		g.make(Move{51, 35});
		should(g.fen().substr(g.fen().find_first_of(' '), 8), " b - d3 ");
		should(pm(g.moves(36)), ",e4e3,e4d3");
		g.make(Move{36, 43});
		should(g.fen().substr(0, 24), "8/8/8/8/8/3p4/8/8 w - - ");
	});

	test("bishops do not take en passant", []() {
		Game g;
		g.start("8/4b3/8/8/8/8/P7/8");
		g.make(Move{48, 32});
		g.make(Move{12, 40});
		should(g.fen().substr(0, 17), "8/8/8/8/P7/b7/8/8");
	});

	test("rook cannot be taken with en passant", []() {
		Game g;
		g.start("/r");
		g.make(Move{8, 24});
		should(g.fen().substr(0, 22), "8/8/8/r7/8/8/8/8 b - -");
	});
}
