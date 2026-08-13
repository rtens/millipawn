#include "../lib/include/Game.h"
#include "base.h"

void restoring() {
	test("empty board", []() {
		Game g;
		should(g.turn, Game::WHITE);
		should(g.fen().substr(0, 15), "8/8/8/8/8/8/8/8");
	});

	test("starting position", []() {
		Game g;
		g.start(Game::STARTPOS);
		should(g.turn, Game::WHITE);
		should(g.fen(), Game::STARTPOS);
	});

	test("mixed position", []() {
		Game g;
		string mixed = "3r2B1/p3pp2/5Q2/kN3RpP/3P2P1/6P1/2PP2PP/7K";
		g.start(mixed);
		should(g.fen().substr(0, mixed.length()), mixed);
	});

	test("blacks turn", []() {
		Game g;
		g.start("/////// b");
		should(g.fen().substr(16, 1), "b");
	});

	test("overwrite pieces", []() {
		Game g;
		g.start("P");
		g.start("8/P");
		should(g.fen().substr(0, 16), "8/P7/8/8/8/8/8/8");
	});

	test("castling", []() {
		Game g;
		g.start("/ w KQkq");
		should(g.fen().substr(17, 6), " KQkq ");
		g.start("/ w Kq");
		should(g.fen().substr(17, 4), " Kq ");
		g.start("/");
		should(g.fen().substr(17, 3), " - ");
		g.start("/ w -");
		should(g.fen().substr(17, 3), " - ");
	});

	test("en passant", []() {
		Game g;
		g.start("/ w - g3");
		should(g.fen().substr(19, 4), " g3 ");
		g.start("/");
		should(g.fen().substr(19, 3), " - ");
		g.start("/ w - -");
		should(g.fen().substr(19, 3), " - ");
	});
}