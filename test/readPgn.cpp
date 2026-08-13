#include "../lib/include/Game.h"
#include "base.h"

void readPgn() {
	test("empty pgn", []() {
		Game g;
		g.start();
		g.apply("");
		should(g.fen(), Game::STARTPOS);
	});

	test("pawn move", []() {
		Game g;
		g.start("//////3P");
		g.apply("d3");
		should(g.fen().substr(0, 17), "8/8/8/8/8/3P4/8/8");
	});

	test("piece move", []() {
		Game g;
		g.start("///3K");
		g.apply("Kd6");
		should(g.fen().substr(0, 17), "8/8/3K4/8/8/8/8/8");
	});

	test("several moves", []() {
		Game g;
		g.start("r///2P");
		g.apply("c6 Ra6");
		should(g.fen().substr(0, 18), "8/8/r1P5/8/8/8/8/8");
	});

	test("file disambiguation", []() {
		Game g;
		g.start("/1R3R");
		g.apply("Rfd7");
		should(g.fen().substr(0, 19), "8/1R1R4/8/8/8/8/8/8");
	});

	test("rank disambiguation", []() {
		Game g;
		g.start("/1R///1R");
		g.apply("R4b5");
		should(g.fen().substr(0, 19), "8/1R6/8/1R6/8/8/8/8");
	});

	test("file and rank disambiguation", []() {
		Game g;
		g.start("1Q////1Q3Q");
		g.apply("Qb4d6");
		should(g.fen().substr(0, 21), "1Q6/8/3Q4/8/5Q2/8/8/8");
	});

	test("invalid move", []() {
		Game g;
		g.start("r///3B");
		g.apply("Bd6 Ra1");
		should(g.fen().substr(0, 18), "r7/8/8/3B4/8/8/8/8");
	});

	test("check", []() {
		Game g;
		g.start("/4k//////R w");
		g.apply("Re1+ Kd7!");
		should(g.fen().substr(0, 19), "8/3k4/8/8/8/8/8/4R3");
	});

	test("piece capture", []() {
		Game g;
		g.start("//2r//1R2b w");
		g.apply("Rxe4 Rc4");
		should(g.fen().substr(0, 19), "8/8/8/8/2r1R3/8/8/8");
	});

	test("pawn capture", []() {
		Game g;
		g.start("/3p/2P1P");
		g.apply("exd7");
		should(g.fen().substr(0, 19), "8/3P4/2P5/8/8/8/8/8");
	});

	test("promotion", []() {
		Game g;
		g.start("/3P");
		g.apply("d8=R");
		should(g.fen().substr(0, 17), "3R4/8/8/8/8/8/8/8");
	});

	test("castle queen-side white", []() {
		Game g;
		g.start("///////R3K2R w KQ");
		g.apply("O-O-O");
		should(g.fen().substr(0, 19), "8/8/8/8/8/8/8/2KR3R");
	});

	test("castle king-side white", []() {
		Game g;
		g.start("///////R3K2R w KQ");
		g.apply("O-O");
		should(g.fen().substr(0, 19), "8/8/8/8/8/8/8/R4RK1");
	});

	test("castle queen-side black", []() {
		Game g;
		g.start("r3k2r b kq");
		g.apply("O-O-O");
		should(g.fen().substr(0, 19), "2kr3r/8/8/8/8/8/8/8");
	});

	test("castle king-side black", []() {
		Game g;
		g.start("r3k2r b kq");
		g.apply("O-O");
		should(g.fen().substr(0, 19), "r4rk1/8/8/8/8/8/8/8");
	});
}