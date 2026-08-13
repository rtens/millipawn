#include "../lib/include/Puzzle.h"

#include "../lib/include/Game.h"
#include "base.h"

void puzzle() {
	test("solved puzzle", []() {
		Game g;
		Puzzle p(&g);
		p.start("", {});
		should(g.fen(), Game::STARTPOS, "start");
		should(p.propose(Move{62, 62 - 17}), Puzzle::SOLVED);
		should(g.fen(), Game::STARTPOS, "end");
	});

	test("solve puzzle", []() {
		Game g;
		Puzzle p(&g);
		p.start("e4 e5", {"g1f3"});
		should(p.propose(Move{62, 62 - 17}), Puzzle::SOLVED);
	});

	test("right move", []() {
		Game g;
		Puzzle p(&g);
		p.start("e4 e5", {"g1f3", "b8c6", "f1c4"});
		should(p.propose(Move{62, 62 - 17}), Puzzle::RIGHT);
	});

	test("multiple steps", []() {});

	test("wrong move", []() {
		Game g;
		Puzzle p(&g);
		p.start("e4 e5", {"g1f3"});
		should(p.propose(Move{61, 61 - 9}), Puzzle::WRONG);
	});

	test("correct wrong move", []() {});
}