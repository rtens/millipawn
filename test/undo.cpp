#include "../lib/include/Game.h"
#include "base.h"

void undo() {
	test("nothing to undo", []() {
		Game g;
		g.start("//3R/PP3K");
		g.undo();
		should(g.fen().substr(0, 23), "8/8/3R4/PP3K2/8/8/8/8 w");
	});

	test("simple move", []() {
		Game g;
		g.start("//3R/PP3K");
		g.make(Move{19, 3});
		should(g.fen().substr(0, 23), "3R4/8/8/PP3K2/8/8/8/8 b");
		g.undo();
		should(g.fen().substr(0, 23), "8/8/3R4/PP3K2/8/8/8/8 w");
	});

	test("capture", []() {
		Game g;
		g.start("3b//3R/PP3K");
		g.make(Move{19, 3});
		should(g.fen().substr(0, 23), "3R4/8/8/PP3K2/8/8/8/8 b");
		g.undo();
		should(g.fen().substr(0, 25), "3b4/8/3R4/PP3K2/8/8/8/8 w");
	});

	test("promotion", []() {
		Game g;
		g.start("/3P");
		g.make(Move{11, 3, Game::QUEEN});
		g.undo();
		should(g.fen().substr(0, 5), "8/3P4");
	});

	test("en passant white", []() {
		Game g;
		g.start("///2Pp w - d6");
		g.make(Move{26, 19});
		g.undo();
		should(g.fen().substr(0, 26), "8/8/8/2Pp4/8/8/8/8 w - d6 ");
	});

	test("en passant black", []() {
		Game g;
		g.start("////2Pp b - c3");
		g.make(Move{35, 42});
		g.undo();
		should(g.fen().substr(0, 26), "8/8/8/8/2Pp4/8/8/8 b - c3 ");
	});

	test("restore en passant", []() {
		Game g;
		g.start("r////2Pp b - c3");
		g.make(Move{0, 1});
		g.undo();
		should(g.fen().substr(0, 27), "r7/8/8/8/2Pp4/8/8/8 b - c3 ");
	});

	test("castling", []() {
		Game g;
		g.start("r3k2r///////R3K2R w KQkq");

		g.make(Move{4, 2});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");

		g.make(Move{4, 6});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");

		g.make(Move{60, 58});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");

		g.make(Move{60, 62});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");

		g.make(Move{0, 8});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");

		g.make(Move{56, 48});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");

		g.make(Move{4, 12});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");
	});
}
